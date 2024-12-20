#pragma once
#include "AsianOption.h"

class AsianCallOption : public AsianOption
{
private :
	double _strike;
public :
	AsianCallOption(std::vector<double> times, double strike);
	double payoff(double spot) const override;
	friend class BlackScholesMCPricer;
};

