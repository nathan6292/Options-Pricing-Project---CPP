#pragma once
#include "Option.h"
#include "optionType.h"

class EuropeanVanillaOption : public Option
{

private: 
	double _strike;
protected:
	optionType _type;
	
public: 
	EuropeanVanillaOption(double, double);
	virtual optionType GetOptionType() const = 0;	
	double payoff(double) const;
	friend class BlackScholesPricer;
};

