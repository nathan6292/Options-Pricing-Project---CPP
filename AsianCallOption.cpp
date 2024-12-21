#include "AsianCallOption.h"
#include <stdexcept>
AsianCallOption::AsianCallOption(std::vector<double> times, double strike) : AsianOption(times) {
	if (strike < 0)
		throw std::invalid_argument("Strike must be positive");

	_type = optionType::Call; 
	_strike = strike;
}

double AsianCallOption::payoff(double mean_spot) const {
	return std::max(mean_spot - _strike, 0.0);
}