#include "EuropeanDigitalOption.h"
#include <stdexcept>
#include <algorithm>

EuropeanDigitalOption::EuropeanDigitalOption(double expiry, double strike) : Option(expiry) {
	if (expiry < 0)
		throw std::invalid_argument("Expiry must be positive");
	if (strike < 0)
		throw std::invalid_argument("Strike must be positive");

	_strike = strike;
}

optionType EuropeanDigitalOption::GetOptionType() const {
	return _type;
}

double EuropeanDigitalOption::payoff(double spot) const {
	if (_type == optionType::Call)
        if(spot >= _strike)
            return 1;
        else
            return 0;
	else
		if(spot <= _strike)
            return 1;
        else
            return 0;
}
