#pragma once
#include "AmericanOption.h"
#include "optionType.h"

class AmericanCallOption : public AmericanOption
{
public: 
	AmericanCallOption(double, double);
	optionType GetOptionType() const;
	double payoff(double) const override;
};

