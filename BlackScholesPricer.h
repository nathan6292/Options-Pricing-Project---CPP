#pragma once
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"
#include "AsianOption.h"

//Declaration of the class BlackScholesPricer
class BlackScholesPricer
{
	//Declaration of the private variables _option_vanilla, _option_digital, _asset_price, _interest_rate and _volatility
private:
	EuropeanVanillaOption* _option_vanilla;
	EuropeanDigitalOption* _option_digital;
	double _asset_price;
	double _interest_rate;
	double _volatility;


public:
	//Declaration of the constructor with the parameters asset_price, interest_rate and volatility for an EuropeanVanillaOption
	BlackScholesPricer(EuropeanVanillaOption*, double, double, double);

	//Declaration of the constructor with the parameters asset_price, interest_rate and volatility for an EuropeanDigitalOption
	BlackScholesPricer(EuropeanDigitalOption*, double, double, double);

	//Declaration of the function operator() that returns the price of the option
	double operator()() const;

	//Declaration of the function delta that returns the delta of the option (derivative of the price with respect to the asset price)
	double delta() const;
};

