#include "EuropeanDigitalPutOption.h"

EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike) : EuropeanDigitalOption(expiry, strike) {
	_type = optionType::Put;
}

double EuropeanDigitalPutOption::payoff(double spot) const {
	if (spot <= _strike)
		return 1;
	else
		return 0;
}

optionType EuropeanDigitalPutOption::GetOptionType() const {
	return _type;
}
