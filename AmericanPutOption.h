#pragma once
#include "AmericanOption.h"	
class AmericanPutOption : public AmericanOption
{
private:
	optionType _type;
public:
	AmericanPutOption(double, double);
	double payoff(double) const override;
	optionType GetOptionType() const;	
};

