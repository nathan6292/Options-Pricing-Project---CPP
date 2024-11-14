#pragma once
#include "Option.h"
#include "optionType.h"
class EuropeanDigitalOption : public Option
{
private :
	double _strike; 
protected:
	optionType _type;
public:
	EuropeanDigitalOption(double, double);
	double payoff(double) const;
	friend class BlackScholesPricer;
};

