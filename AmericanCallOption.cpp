#include "AmericanCallOption.h"
#include <algorithm> // pour std::max

AmericanCallOption::AmericanCallOption(double expiry, double strike)
    : AmericanOption(expiry, strike) {}

double AmericanCallOption::payoff(double S) const {
    return std::max(S - _strike, 0.0);
}
