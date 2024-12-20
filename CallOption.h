#pragma once
#include "EuropeanVanillaOption.h"

class CallOption : public EuropeanVanillaOption
{
private: 
	optionType _type;
public:
	CallOption(double, double);
	optionType GetOptionType() const override;
	double payoff(double) const;
};

