#pragma once
#include "Option.h"
#include "optionType.h"
class EuropeanDigitalOption : public Option
{
private :
	double _strike; 
public:
	EuropeanDigitalOption(double, double);
	virtual optionType GetOptionType() const=0;
	friend class BlackScholesPricer;
	friend class EuropeanDigitalPutOption;
	friend class EuropeanDigitalCallOption;
};

