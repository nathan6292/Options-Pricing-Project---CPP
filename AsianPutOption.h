#pragma once
#include "AsianOption.h"

class AsianPutOption : public AsianOption
{
private:
	double _strike;
	optionType _type;
public:
	AsianPutOption(std::vector<double> times, double strike);
	double payoff(double spot) const override;
};

