#include "AmericanOption.h"

AmericanOption::AmericanOption(double expiry, double strike)
    : option(expiry), _strike(strike) {}

bool AmericanOption::isAmericanOption() const {
    return true;
}
