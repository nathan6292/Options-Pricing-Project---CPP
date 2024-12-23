#pragma once
#include "AmericanOption.h"	

// Declaration of the class AmericanPutOption
class AmericanPutOption : public AmericanOption
{
	// Declaration of the private variable type (put)
private:
	optionType _type;
public:
	// Declaration of the constructor with the parameters strike and expiry
	AmericanPutOption(double, double);

	// Declaration of the destructor
	~AmericanPutOption();

	// Declaration of the overriden function payoff that returns the payoff of the option at a given spot price
	double payoff(double) const override;

	// Declaration of the function GetOptionType that returns the type of the option
	optionType GetOptionType() const;	
};

