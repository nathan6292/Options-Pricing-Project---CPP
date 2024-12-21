#include "AmericanCallOption.h"

AmericanCallOption::AmericanCallOption(double expiry, double strike) : AmericanOption(expiry, strike) {
	_type = optionType::Call;
}

double AmericanCallOption::payoff(double spot) const {
	return std::max(spot - _strike, 0.0);
}

optionType AmericanCallOption::GetOptionType() const {
	return _type;
}
