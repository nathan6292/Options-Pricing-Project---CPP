#pragma once
#include "AsianOption.h"

class AsianPutOption : public AsianOption {
private:
    double strike;  // Strike price
public:
    AsianPutOption(double expiry, const std::vector<double>& timeSteps, double strike);

    // Payoff for Asian Put Option
    double payoff(double underlyingPrice) const override;

    // Override payoffPath to calculate average price path for Asian Put
    double payoffPath(const std::vector<double>& assetPath) const override;
};
