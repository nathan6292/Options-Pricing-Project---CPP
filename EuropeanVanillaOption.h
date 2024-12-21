#pragma once
#include "Option.h"
#include "optionType.h"

//Declaration of the class EuropeanVanillaOption that inherits from the class Option
class EuropeanVanillaOption : public Option
{
	//Declaration of the private variable strike
private:
	double _strike;

public: 
	//Declaration of the constructor with the parameters strike and expiry
	EuropeanVanillaOption(double, double);

	//Declaration of the pure virtual function GetOptionType, that returns the option type (Call or Put) 
	//This function is defined in the derived classes
	virtual optionType GetOptionType() const = 0;	

	//Define BlackScholesPricer, CallOption and PutOption as friend classes to access the private variables
	friend class BlackScholesPricer;
	friend class CallOption;
	friend class PutOption;
};

