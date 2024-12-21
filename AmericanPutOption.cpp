#include "AmericanPutOption.h"

AmericanPutOption::AmericanPutOption(double expiry, double strike) : AmericanOption(expiry, strike) {
	_type = optionType::Put;
}

double AmericanPutOption::payoff(double spot) const {
		return std::max(_strike - spot, 0.0);
}

optionType AmericanPutOption::GetOptionType() const {
	return _type;
}