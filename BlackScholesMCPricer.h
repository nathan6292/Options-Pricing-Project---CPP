#pragma once
#include "Option.h"
#include "AsianOption.h"
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"
#include "MT.h"

class BlackScholesMCPricer
{
private:
	int npaths; 
	Option* _option;
	double _initial_price;
	double _volatility;
	double _interest_rate;  
	double sum;
	double sum_squared;

public:
	BlackScholesMCPricer(Option*, double, double, double);
	int getNbPaths(); 
	void generate(int nb_paths);
	double operator()();
	std::vector<double> confidenceInterval(); 

};

