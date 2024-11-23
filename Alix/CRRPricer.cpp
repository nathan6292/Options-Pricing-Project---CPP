#include "CRRPricer.h"
#include "BinaryTree.h"
#include <stdexcept>
#include <cmath>

double power(double x, int n) {
    double result = 1.0;
    while (n > 0) {
        if (n % 2 == 1) result *= x;
        x *= x;
        n /= 2;
    }
    return result;
}

// Constructor with up, down and interest rate
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate){

    // Check if the option is an Asian option to throw an exception
	if (option->isAsianOption()) {
		throw std::invalid_argument("The option is an Asian Option!");
	}

	if (interest_rate >= up || interest_rate <= down)
		throw std::invalid_argument("The model admits Arbitrage!");

	this->option = option;
	this->depth = depth;
	this->asset_price = asset_price;
	this->up = up;
	this->down = down;
	this->interest_rate = interest_rate;
	
    tree.setDepth(depth); // Initialise the depth of the tree
    tree_bool.setDepth(depth);
}
// Constructor with r and volatility that compute up, down and interest rate
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r, double volatility) {

	if (option->isAsianOption()) {
		throw std::invalid_argument("The option is an Asian Option!");
	}

	this->option = option;
	this->depth = depth;
	this->asset_price = asset_price;
    //U = exp^[(r+σ*σ/2)*h+σ√h]− 1
	this->up = std::exp((r+ (volatility * volatility) / 2) * (option->getExpiry() / depth) + volatility * std::sqrt(option->getExpiry() / depth)) - 1;
    //D = exp^[(r+σ*σ/2)*h-σ√h]− 1
	this->down = std::exp((r + (volatility * volatility) / 2) * (option->getExpiry() / depth) - volatility * std::sqrt(option->getExpiry() / depth)) - 1;
    //R = exp^(rh − 1)
	this->interest_rate = std::exp(r*(option->getExpiry()/ depth))-1;

	if (interest_rate >= up || interest_rate <= down)
		throw std::invalid_argument("The model admits Arbitrage!");

	tree.setDepth(depth); // Initialise the depth of the tree
    tree_bool.setDepth(depth);
}

//This method constructs a binary tree of option values using the Cox-Rox-Robinson method
//It first calculates the value of the last level of the tree (at expiry) by applying the option's payoff method
//She then goes back up the tree using the formula given in the statement
void CRRPricer::compute() {
    // Initialise values at expiry level N
    for (int i = 0; i <= depth; ++i) {
        double final_price = asset_price * std::pow(1 + up, i) * std::pow(1 + down, depth - i); //we simply use the formula S(N,i)=S0*U^i*D^(N-i)
        tree.setNode(depth, i, option->payoff(final_price));
        tree_bool.setNode(depth, i, false); // On expiry, there's no question of early exercise
    }
    // Induction to calculate values at previous levels
	double q = (interest_rate - down) / (up - down);
	if (option->isAmericanOption()) {
		for (int i = depth - 1; i >= 0; i--) {//go back up the tree by calculating the value of the option at each node
			for (int j = 0; j <= i; j++) {
				double continuous_value = (q * tree.getNode(i + 1, j + 1) + (1 - q) * tree.getNode(i + 1, j)) / (1 + interest_rate); 
				double intrinsic_value = option->payoff(asset_price * power(1 + up, j) * power(1 + down, i - j));
				tree.setNode(i, j, std::max(continuous_value, intrinsic_value));
                // Set the exercise policy for American options
				tree_bool.setNode(i, j, continuous_value <= intrinsic_value);
			}
		}
	}
	else {
		for (int i = depth - 1; i >= 0; i--) {//go back up the tree by calculating the value of the option at each node
			for (int j = 0; j <= i; j++) {
				tree.setNode(i, j, (q * tree.getNode(i + 1, j + 1) + (1 - q) * tree.getNode(i + 1, j)) / (1 + interest_rate));
			}
		}
	}
	tree.display();
}

double CRRPricer::get(int i, int j) {
    if (j < 0 || i < 0 || j > depth || i > depth) {
        throw std::out_of_range("Invalid tree indices");
    }
	return tree.getNode(i, j);
}

// This method calculates and returns the option price 
//If the argument is true, it calculates the option price without passing through the abbreviation, otherwise it uses the compute method
double CRRPricer::operator()(bool closed_form) {
	if (!closed_form)
    {
		compute();
        // We return the H(0,0) already compute with the standard method
		return get(0, 0);
	}
	//closed-form formula for option pricing
    else 
    {
        // Closed form for European options only
        if (option->isAmericanOption()) {
            throw std::invalid_argument("Closed formula not available for American options");
        }
		double q = (interest_rate - down) / (up - down);
		double sum = 0;
		// The binomial coefficient is equal to 1 at the beginning because at i = 0 it is N!/N!
        double binomial_coefficient = 1;
		for (int i = 0; i <= depth; i++) {
            //We will use the formula provide and we have : tree.getNode(depth-1,i) = H(N,i) 
			sum += binomial_coefficient*power(q,i)*power(1-q,depth-i-1)*tree.getNode(depth-1,i);
            //binomial_coefficient = N!/(i!(N − i)!)
			binomial_coefficient = binomial_coefficient * (depth - i - 1) / (i + 1);
		}
		return (1 / power(1 + interest_rate, depth-1)) * sum;
	}
}

bool CRRPricer::getExercise(int i, int j) {
    if (j < 0 || i < 0 || j > depth || i > depth) {
        throw std::out_of_range("Invalid tree indices");
    }
	return tree_bool.getNode(i, j);
}
