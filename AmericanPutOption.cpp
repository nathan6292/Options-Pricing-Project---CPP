#include "AmericanPutOption.h"
#include <algorithm> // pour std::max

AmericanPutOption::AmericanPutOption(double expiry, double strike)
    : AmericanOption(expiry, strike) {}

double AmericanPutOption::payoff(double S) const {
    return std::max(_strike - S, 0.0);
}
