#include "EuropeanVanillaOption.h"
#include <stdexcept>
#include <algorithm>

EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike) : Option(expiry) {
	if (expiry < 0)
		throw std::invalid_argument("Expiry must be positive");
	if (strike < 0)
		throw std::invalid_argument("Strike must be positive");

	_strike = strike;
}

optionType EuropeanVanillaOption::GetOptionType() const {
	return _type;
}

double EuropeanVanillaOption::payoff(double spot) const {
	if (_type == optionType::Call)
		return std::max((spot - _strike), 0.0);
	else
		return std::max((_strike - spot), 0.0);
}