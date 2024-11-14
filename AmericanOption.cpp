#include "AmericanOption.h"

AmericanOption::AmericanOption(double expiry, double strike) : Option(expiry), _strike(strike) {}

bool AmericanOption::isAmericanOption() const {
	return true;
}

double AmericanOption::payoff(double spot) const {
	if (_type == optionType::Call) {
		return std::max(spot - _strike, 0.0);
	}
	else {
		return std::max(_strike - spot, 0.0);
	}
}
