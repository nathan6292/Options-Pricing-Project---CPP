#pragma once
#include "EuropeanDigitalOption.h"

// Declaration of the class EuropeanDigitalPutOption
class EuropeanDigitalPutOption : public EuropeanDigitalOption
{
	// Declaration of the private variable type (put)
private:
	optionType _type;
public:
	// Declaration of the constructor with the parameters strike and expiry
	EuropeanDigitalPutOption(double, double);

	//Destructor
	~EuropeanDigitalPutOption();

	// Declaration of the overriden function GetOptionType that returns the type of the option (put)
	optionType GetOptionType() const override;

	// Declaration of the function payoff that returns the payoff of the option
	double payoff(double) const;
};

