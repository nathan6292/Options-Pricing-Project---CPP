#include "CRRPricer.h"

double power(double x, int n) {
	if (n == 0) return 1;
	double half = power(x, n / 2);
	if (n % 2 == 0) return half * half;
	else return x * half * half;
}

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate){

	if ((*option).isAsianOption()) {
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
	
	tree = BinaryTree<double>(depth);
	tree_bool = BinaryTree<bool>(depth);

	for (int i = 0; i < depth; i++) {
		double final_price = asset_price * power(1+up, i) * power(1+down, depth-i-1);
		tree.setNode(depth-1,i,(*option).payoff(final_price));
	}
}

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r, double volatility) {

	if ((*option).isAsianOption()) {
		throw std::invalid_argument("The option is an Asian Option!");
	}

	this->option = option;
	this->depth = depth;
	this->asset_price = asset_price;
	this->up = std::exp((r+ (volatility * volatility) / 2) * ((*option).getExpiry() / depth) + volatility * std::sqrt((*option).getExpiry() / depth)) - 1;
	this->down = std::exp((r + (volatility * volatility) / 2) * ((*option).getExpiry() / depth) - volatility * std::sqrt((*option).getExpiry() / depth)) - 1;
	this->interest_rate = std::exp(r*((*option).getExpiry()/ depth))-1;

	if (interest_rate >= up || interest_rate <= down)
		throw std::invalid_argument("The model admits Arbitrage!");

	tree = BinaryTree<double>(depth);
	tree_bool = BinaryTree<bool>(depth);

	for (int i = 0; i < depth; i++) {
		double final_price = asset_price * power(1 + up, i) * power(1 + down, depth - i - 1);
		tree.setNode(depth - 1, i, (*option).payoff(final_price));
	}
}

void CRRPricer::compute() {
	double q = (interest_rate - down) / (up - down);
	if (AmericanOption* americanoption = dynamic_cast<AmericanOption*>(option)) {
		for (int i = depth - 2; i >= 0; i--) {
			for (int j = 0; j <= i; j++) {
				double continuous_value = (q * tree.getNode(i + 1, j + 1) + (1 - q) * tree.getNode(i + 1, j)) / (1 + interest_rate); 
				double intrinsic_value = (*option).payoff(asset_price * power(1 + up, j) * power(1 + down, i - j));
				tree.setNode(i, j, std::max(continuous_value, intrinsic_value));
				tree_bool.setNode(i, j, continuous_value <= intrinsic_value);
			}
		}
	}
	else {
		for (int i = depth - 2; i >= 0; i--) {
			for (int j = 0; j <= i; j++) {
				tree.setNode(i, j, (q * tree.getNode(i + 1, j + 1) + (1 - q) * tree.getNode(i + 1, j)) / (1 + interest_rate));
			}
		}
	}
	//tree.display();
}

double CRRPricer::get(int i, int j) {
	return tree.getNode(i, j);
}


double CRRPricer::operator()(bool closed_form) {
	if (closed_form == false) {
		compute();
		return get(0, 0);
	}
	else {
		double q = (interest_rate - down) / (up - down);
		double sum = 0;
		double binomial_coefficient = 1;
		for (int i = 0; i < depth; i++) {
			sum += binomial_coefficient*power(q,i)*power(1-q,depth-i-1)*tree.getNode(depth-1,i);
			binomial_coefficient = binomial_coefficient * (depth - i - 1) / (i + 1);
		}
		return (1 / power(1 + interest_rate, depth-1)) * sum;
	}
}

bool CRRPricer::getExercise(int i, int j) {
	return tree_bool.getNode(i, j);
}