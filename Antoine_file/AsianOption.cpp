#include "AsianOption.h"

// Constructor implementation
AsianOption::AsianOption(double expiry, const std::vector<double>& timeSteps)
    : option(expiry), _timeSteps(timeSteps) {}

// Getter implementation for time steps
const std::vector<double>& AsianOption::getTimeSteps() const {
    return _timeSteps;
}

// Implementation of payoffPath, which calculates the average-based payoff
double AsianOption::payoffPath(const std::vector<double>& prices) const {
    double sum = 0.0;
    for (double price : prices) {
        sum += price;
    }
    double averagePrice = sum / prices.size();
    return payoff(averagePrice);
}

bool AsianOption::isAsianOption() const {
    return true;
}