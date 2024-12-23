#pragma once
#include "EuropeanVanillaOption.h"

//Declaration of the class PutOption that inherits from the class EuropeanVanillaOption
class PutOption : public EuropeanVanillaOption
{
	//Declaration of the private variable _type (Put)
private:
	optionType _type;
public:
	//Declaration of the constructor with the parameters expiry and strike
	PutOption(double, double);

	//Destructor
	~PutOption();

	//Declaration of the overriden function GetOptionType that returns the option type (Put)
	optionType GetOptionType() const override;

	//Declaration of the overriden function payoff that returns the payoff of the option
	double payoff(double) const override;
};

