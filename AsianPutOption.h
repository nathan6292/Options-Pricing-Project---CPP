#pragma once
#include "AsianOption.h"

class AsianPutOption : public AsianOption
{
private:
	double _strike;
public:
	AsianPutOption(std::vector<double> times, double strike);
	double payoff(double spot) const override;
	friend class BlackScholesMCPricer;
};

