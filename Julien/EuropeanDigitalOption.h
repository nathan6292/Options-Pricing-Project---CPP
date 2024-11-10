#pragma once
#include<iostream>
#include"Option.h"
#include"optionType.h"
using namespace std;

class EuropeanDigitalOption : public Option
{
public:
	EuropeanDigitalOption(double, double); //pas besoin de mettre strike et expiry direct là
	virtual optionType GetOptionType()const = 0;
	double payoff(double) const override; //pas besoin de réécrire virtual (déjà écrit dans classe mère)
	friend class BlackScholesPricer;
private:
	double _strike;
protected:
	optionType _type; //si pas en protected, type pas reconnu dans classes calloption et putoption
};
