#pragma once
#include "AmericanOption.h"
#include "optionType.h"

// Declaration of the class AmericanCallOption
class AmericanCallOption : public AmericanOption
{
	// Declaration of the private variable type (call)
private:
	optionType _type;

public: 
	// Declaration of the constructor with the parameters strike and expiry
	AmericanCallOption(double, double);

	// Declaration of the function GetOptionType that returns the type of the option
	optionType GetOptionType() const;

	// Declaration of the function payoff that returns the payoff of the option
	double payoff(double) const override;
};

