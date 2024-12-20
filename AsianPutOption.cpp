#include "AsianPutOption.h"
#include <stdexcept>
AsianPutOption::AsianPutOption(std::vector<double> times, double strike) : AsianOption(times) {
	if (strike < 0)
		throw std::invalid_argument("Strike must be positive");

	_strike = strike;
	_type = optionType::Put;
}

double AsianPutOption::payoff(double spot) const {
	return std::max(_strike - spot, 0.0);
}