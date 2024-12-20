#include "EuropeanDigitalCallOption.h"

EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike) : EuropeanDigitalOption(expiry, strike) {
	_type = optionType::Call;
}

double EuropeanDigitalCallOption::payoff(double spot) const {
	if (spot >= _strike)
		return 1;
	else
		return 0;
}

optionType EuropeanDigitalCallOption::GetOptionType() const {
	return _type;
}