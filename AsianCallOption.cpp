#include "AsianCallOption.h"
#include <algorithm> // For std::max

AsianCallOption::AsianCallOption(double expiry, const std::vector<double>& timeSteps, double strike)
    : AsianOption(expiry, timeSteps), strike(strike) {}

double AsianCallOption::payoff(double underlyingPrice) const {
    return std::max(underlyingPrice - strike, 0.0);  // Payoff for vanilla call
}

double AsianCallOption::payoffPath(const std::vector<double>& assetPath) const {
    double sum = 0.0;
for (double price : assetPath) {
    sum += price;
}
double averagePrice = sum / assetPath.size();
    return std::max(averagePrice - strike, 0.0);
}

