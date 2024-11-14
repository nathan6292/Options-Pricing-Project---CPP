#pragma once
#include "AsianOPtion.h"	
#include <algorithm> // pour std::max

class AsianCallOption : public AsianOption
{
private :
	double strike;
public :

    AsianCallOption(double expiry, const std::vector<double>& timeSteps, double strike);

    // Payoff for Asian Call Option
    double payoff(double underlyingPrice) const override;

    // Override payoffPath to calculate average price path for Asian Call
    double payoffPath(const std::vector<double>& assetPath) const override;
};

