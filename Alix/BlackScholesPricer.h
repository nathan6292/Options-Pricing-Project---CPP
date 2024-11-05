#pragma once
#include "EuropeanVanillaOption.h"

class BlackScholesPricer
{
	EuropeanVanillaOption* _option;
	double _asset_price;
	double _interest_rate;
	double _volatility;


public:
	BlackScholesPricer(EuropeanVanillaOption*, double, double, double);
	double operator()() const;
	double delta() const;
};