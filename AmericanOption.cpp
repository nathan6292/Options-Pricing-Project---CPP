#include "AmericanOption.h"

// Constructor with the parameters strike and expiry
AmericanOption::AmericanOption(double expiry, double strike) : Option(expiry), _strike(strike) {}

// Overridden function isAmericanOption that returns true
bool AmericanOption::isAmericanOption() const {
	return true;
}


