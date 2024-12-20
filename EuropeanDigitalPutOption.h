#pragma once
#include "EuropeanDigitalOption.h"

class EuropeanDigitalPutOption : public EuropeanDigitalOption
{
private:
	optionType _type;
public:
	EuropeanDigitalPutOption(double, double);
	optionType GetOptionType() const override;
	double payoff(double) const;
};

