#pragma once
#include "Option.h"
#include "optionType.h"
class AmericanOption : public Option
{
protected: 
	double _strike;
	optionType _type;
public: 
	AmericanOption(double, double);
	bool isAmericanOption() const override;
	double payoff(double) const override;
};

