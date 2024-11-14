#include "AsianPutOption.h"
#include <algorithm> // For std::max

AsianPutOption::AsianPutOption(double expiry, const std::vector<double>& timeSteps, double strike)
    : AsianOption(expiry, timeSteps), strike(strike) {}

double AsianPutOption::payoff(double underlyingPrice) const {
    return std::max(strike - underlyingPrice, 0.0);  // Payoff for vanilla put
}

double AsianPutOption::payoffPath(const std::vector<double>& assetPath) const {
    double sum = 0.0;
    for (double price : assetPath) {
        sum += price;
    }
    double averagePrice = sum / assetPath.size();
    return std::max(strike - averagePrice, 0.0);
}

