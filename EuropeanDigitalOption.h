#pragma once
#include "Option.h"
#include "optionType.h"

// Declaration of the class EuropeanDigitalOption
class EuropeanDigitalOption : public Option
{
	// Declaration of the private variable strike
private :
	double _strike; 
public:
	// Declaration of the constructor with the parameters strike and expiry
	EuropeanDigitalOption(double, double);

	// Destructor
	~EuropeanDigitalOption();

	// Declaration of the pure virtual function payoff that returns the payoff of the option
	virtual optionType GetOptionType() const=0;


	// Defines BlackScholesPrices, EuropeanDigitalPutOption and EuropeanDigitalCallOption as friend classes to access the strike
	friend class BlackScholesPricer;
	friend class EuropeanDigitalPutOption;
	friend class EuropeanDigitalCallOption;
};

