#include "AmericanOption.h"

AmericanOption::AmericanOption(double expiry, double strike) : Option(expiry), _strike(strike) {}

bool AmericanOption::isAmericanOption() const {
	return true;
}


