#pragma once
#include "AsianOption.h"

// Declaration of the class AsianPutOption
class AsianPutOption : public AsianOption
{
	// Declaration of the private variables _strike and _type (Put)
private:
	double _strike;
	optionType _type;
public:
	// Declaration of the constructor with the parameters times and strike
	AsianPutOption(std::vector<double> times, double strike);

	// Declaration of the overriden function payoff that returns the payoff of the option
	double payoff(double spot) const override;
};

