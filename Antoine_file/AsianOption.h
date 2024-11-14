#pragma once
#include "option.h"
#include <vector>

class AsianOption : public option {
private:
    std::vector<double> _timeSteps;

public:
    // Constructor 
    AsianOption(double expiry, const std::vector<double>& timeSteps);

    // Getter pour timesteps
    const std::vector<double>& getTimeSteps() const;

    // Override payoffPath to calculate the payoff based on the average of prices
    double payoffPath(const std::vector<double>& prices) const;

    bool isAsianOption() const override;

    // Destructeur ou cas ou
    virtual ~AsianOption() {}
};
