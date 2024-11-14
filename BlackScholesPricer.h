#pragma once
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"
#include "AsianOption.h"

class BlackScholesPricer
{
	Option* _option;
	double _asset_price;
	double _interest_rate;
	double _volatility;


public:
	BlackScholesPricer(Option*, double, double, double);
	double operator()() const;
	double delta() const;
};

