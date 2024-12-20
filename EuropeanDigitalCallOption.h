#pragma once
#include "EuropeanDigitalOption.h"

class EuropeanDigitalCallOption : public EuropeanDigitalOption
{
private:
	optionType _type;
public:
	EuropeanDigitalCallOption(double, double);
	optionType GetOptionType() const override;
	double payoff(double) const;
};

