#pragma once
#include "Option.h"
#include "optionType.h"

class EuropeanVanillaOption : public Option
{
protected:
	optionType _type;
	double _strike;
public: 
	EuropeanVanillaOption(double, double);
	virtual optionType GetOptionType() const = 0;	
	friend class BlackScholesPricer;
};

