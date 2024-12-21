#include "CRRPricer.h"


/// <summary>
/// Compute the power of a number x to the power n
/// 
/// We do not use the std::pow function because it is not efficient for large values of n
/// 
/// We use the exponentiation by squaring algorithm
/// 
/// The complexity of this algorithm is O(log(n))
/// </summary>
/// <param name="x">number</param>
/// <param name="n">power</param>
/// <returns></returns>
double power(double x, int n) {
	double result = 1.0;

	while (n > 0) {
		if (n % 2 == 1) result *= x;
		x *= x;
		n /= 2;
	}
	return result;
}

/// <summary>
/// Constructor with the parameters option, depth, asset_price, up, down and interest_rate
/// </summary>
/// <param name="option">Pointer to the option</param>
/// <param name="depth">Depth of the tree</param>
/// <param name="asset_price">Current price of the underlying asset</param>
/// <param name="up">Up factor</param>
/// <param name="down">Down factor</param>
/// <param name="interest_rate">Risk-free interest rate</param>
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate) {

	// Check if the option is an Asian option to throw an exception
	if (option->isAsianOption()) {
		throw std::invalid_argument("The option is an Asian Option!");
	}

	// Check if the model admits arbitrage
	if (interest_rate >= up || interest_rate <= down)
		throw std::invalid_argument("The model admits Arbitrage!");

	// Initialise the private variables
	this->option = option;
	this->depth = depth;
	this->asset_price = asset_price;
	this->up = up;
	this->down = down;
	this->interest_rate = interest_rate;

	tree.setDepth(depth); // Initialise the depth of the tree
	tree_bool.setDepth(depth); // Initialise the depth of the tree_bool
}

/// <summary>
/// Constructor with the parameters option, depth, asset_price, r and volatility
/// 
/// We convert the continously compounded interest rate r and the volatility into the up, down and interest_rate factors
/// 
/// The goal is to have a more user-friendly constructor and compare the results with the Black-Scholes model
/// 
/// The R in the CRR model is descrete and the r in the Black-Scholes model is continous
/// </summary>
/// <param name="option">Pointer to the option</param>
/// <param name="depth">Depth of the tree</param>
/// <param name="asset_price">Current price of the underlying asset</param>
/// <param name="r">Continously compounded interest rate in the Black-Scholes model</param>
/// <param name="volatility">Volatility of the underlying asset</param>
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r, double volatility) {

	// Check if the option is an Asian option to throw an exception
	if (option->isAsianOption()) {
		throw std::invalid_argument("The option is an Asian Option!");
	}

	// Initialise the private variables
	this->option = option;
	this->depth = depth;
	this->asset_price = asset_price;
	//U = exp^[(r+σ*σ/2)*h+σ√h]− 1
	this->up = std::exp((r + (volatility * volatility) / 2) * (option->getExpiry() / depth) + volatility * std::sqrt(option->getExpiry() / depth)) - 1;
	//D = exp^[(r+σ*σ/2)*h-σ√h]− 1
	this->down = std::exp((r + (volatility * volatility) / 2) * (option->getExpiry() / depth) - volatility * std::sqrt(option->getExpiry() / depth)) - 1;
	//R = exp^(rh − 1)
	this->interest_rate = std::exp(r * (option->getExpiry() / depth)) - 1;


	// Check if the model admits arbitrage
	if (interest_rate >= up || interest_rate <= down)
		throw std::invalid_argument("The model admits Arbitrage!");

	// Initialise the depth of the tree
	tree.setDepth(depth);
	tree_bool.setDepth(depth);
}

/// <summary>
/// Implement the Cox-Ross-Rubinstein model procedure to compute the price of the option
/// 
/// We use the binomial tree to compute the price of the option
/// </summary>
void CRRPricer::compute() {
	// Initialise values at expiry level N
	for (int i = 0; i <= depth; ++i) {
		double final_price = asset_price * std::pow(1 + up, i) * std::pow(1 + down, depth - i); //we simply use the formula S(N,i)=S0*U^i*D^(N-i)
		tree.setNode(depth, i, option->payoff(final_price));
		tree_bool.setNode(depth, i, false); // On expiry, there's no question of early exercise
	}

	// Induction to calculate values at previous levels
	double q = (interest_rate - down) / (up - down);

	// American options
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
	// European options
	else {
		for (int i = depth - 1; i >= 0; i--) {//go back up the tree by calculating the value of the option at each node
			for (int j = 0; j <= i; j++) {
				// Calculate the value of the option at each node
				tree.setNode(i, j, (q * tree.getNode(i + 1, j + 1) + (1 - q) * tree.getNode(i + 1, j)) / (1 + interest_rate));
			}
		}
	}

	// Remove the comments to display the tree
	//tree.display();
}
  
/// <summary>
/// Get the value of the node at the indices i and j (The price of the option at the node (i,j) of the tree)
/// </summary>
/// <param name="i">i-th level of the tree (represents the time)</param>
/// <param name="j">j-th node at the i-th level of the tree (represents the price of the underlying asset at level i depending on previous levels)</param>
/// <returns>Returns the value of the node (i,j)</returns>
double CRRPricer::get(int i, int j) {
	// Check if the indices are valid
	if (j < 0 || i < 0 || j > depth || i > depth) {
		throw std::out_of_range("Invalid tree indices");
	}

	// Return the value of the node (i,j)
	return tree.getNode(i, j);
}


/// <summary>
/// Compute the price of the option using the Cox-Ross-Rubinstein model for European and American options
/// 
/// If closed_form is false, we use the standard method to compute the price of the option
/// </summary>
/// <param name="closed_form">If closed_form is true, we use the closed-form formula to compute the price of the option</param>
/// <returns>Price of the option</returns>
double CRRPricer::operator()(bool closed_form) {
	// If closed_form is false, we use the standard method to compute the price of the option
	if (!closed_form)
	{
		// Compute the price of the option using the tree method only if the tree is not already computed
		if (tree.getNode(0, 0) == 0.0) {
			compute();
		}
		// We return the H(0,0) already compute with the standard method, it corresponds to the price of the option at time 0 (now)
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
		for (int i = 0; i < depth; i++) {
			//We will use the formula provide and we have : tree.getNode(depth-1,i) = H(N,i) 
			sum += binomial_coefficient * power(q, i) * power(1 - q, depth - i - 1) * tree.getNode(depth - 1, i);
			//binomial_coefficient = N!/(i!(N − i)!)
			binomial_coefficient = binomial_coefficient * (depth - i - 1) / (i + 1);
		}
		return (1 / power(1 + interest_rate, depth - 1)) * sum;
	}
}


/// <summary>
/// Returns the exercise policy of the option at the node (i,j) of the tree for American options 
/// 
/// The exercise policy is a boolean value (true if the option is exercised, false otherwise)
/// </summary>
/// <param name="i">i-th level of the tree (represents the time)</param>
/// <param name="j">j-th node at the i-th level of the tree (represents the price of the underlying asset at level i depending on previous levels)</param>
/// <returns>Returns the exercise policy of the option at the node (i,j)</returns>
bool CRRPricer::getExercise(int i, int j) {
	// Check if the indices are valid
	if (j < 0 || i < 0 || j > depth || i > depth) {
		throw std::out_of_range("Invalid tree indices");
	}
	// Return the exercise policy of the option at the node (i,j)
	return tree_bool.getNode(i, j);
}