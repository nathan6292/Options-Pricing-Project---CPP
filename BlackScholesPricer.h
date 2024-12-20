#pragma once
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"
#include "AsianOption.h"

class BlackScholesPricer
{
private:
	EuropeanVanillaOption* _option_vanilla;
	EuropeanDigitalOption* _option_digital;
	double _asset_price;
	double _interest_rate;
	double _volatility;


public:
	BlackScholesPricer(EuropeanVanillaOption*, double, double, double);
	BlackScholesPricer(EuropeanDigitalOption*, double, double, double);
	double operator()() const;
	double delta() const;
};

