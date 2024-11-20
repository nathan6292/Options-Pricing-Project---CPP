#pragma once
#include "Option.h"
#include "optionType.h"


class EuropeanVanillaOption : public Option
{
private:
	double _strike;
public: 
	EuropeanVanillaOption(double, double);
	virtual optionType GetOptionType() const = 0;	
	friend class BlackScholesPricer;
	friend class CallOption;
	friend class PutOption;
};

