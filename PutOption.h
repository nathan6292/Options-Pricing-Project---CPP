#pragma once
#include "EuropeanVanillaOption.h"
class PutOption : public EuropeanVanillaOption
{
private:
	optionType _type;
public:
	PutOption(double, double);
	optionType GetOptionType() const override;
	double payoff(double) const;
};

