#include "AsianCallOption.h"
#include <stdexcept>
#include <cmath>
AsianCallOption::AsianCallOption(std::vector<double> times, double strike) : AsianOption(times) {
	if (strike < 0)
		throw std::invalid_argument("Strike must be positive");

	_type = optionType::Call; 
	_strike = strike;
}

double AsianCallOption::payoff(double spot) const {
	return std::max(spot - _strike, 0.0);
}