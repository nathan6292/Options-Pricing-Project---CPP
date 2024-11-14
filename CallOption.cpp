#include "CallOption.h"

CallOption::CallOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {
	_type = optionType::Call;
}

optionType CallOption::GetOptionType() const {
	return _type;
}

double CallOption::payoff(double spot) const {
	return std::max(spot - _strike, 0.0);
}



