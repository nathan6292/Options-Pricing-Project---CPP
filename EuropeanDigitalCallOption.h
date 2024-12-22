#pragma once
#include "EuropeanDigitalOption.h"

// Declaration of the class EuropeanDigitalCallOption
class EuropeanDigitalCallOption : public EuropeanDigitalOption
{
	// Declaration of the private variable type (call)
private:
	optionType _type;
public:
	// Declaration of the constructor with the parameters strike and expiry
	EuropeanDigitalCallOption(double, double);

	// Declaration of the overriden function GetOptionType that returns the type of the option (call)
	optionType GetOptionType() const override;
	double payoff(double) const;
};

