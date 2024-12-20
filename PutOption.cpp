#include "PutOption.h"

PutOption::PutOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {
	_type = optionType::Put;
}

optionType PutOption::GetOptionType() const {
	return _type;
}

double PutOption::payoff(double spot) const {
		return std::max(_strike - spot, 0.0);
}



