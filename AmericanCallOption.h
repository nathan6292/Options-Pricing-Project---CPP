#pragma once
#include "AmericanOption.h"
#include "optionType.h"

class AmericanCallOption : public AmericanOption
{
private:
	optionType _type;

public: 
	AmericanCallOption(double, double);
	optionType GetOptionType() const;
	double payoff(double) const override;
};

