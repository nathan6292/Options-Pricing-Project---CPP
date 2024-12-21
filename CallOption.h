#pragma once
#include "EuropeanVanillaOption.h"

//Declaration of the class CallOption that inherits from the class EuropeanVanillaOption
class CallOption : public EuropeanVanillaOption
{
	//Declaration of the private variable _type (Call)
private: 
	optionType _type;
public:
	//Declaration of the constructor with the parameters expiry and strike
	CallOption(double, double);

	//Declaration of the overriden function GetOptionType that returns the option type (Call)
	optionType GetOptionType() const override;

	//Declaration of the overriden function payoff that returns the payoff of the option
	double payoff(double) const override;
};

