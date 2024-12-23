#pragma once
#include "Option.h"
#include "AsianOption.h"
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"
#include "MT.h"

//Declaration of the class BlackScholesMCPricer, that calculates the price of an option using the Monte Carlo method
class BlackScholesMCPricer
{
	//Declaration of the private variables npaths, _option, _initial_price, _volatility, _interest_rate, sum and sum_squared
private:
	int npaths; 
	Option* _option;
	double _initial_price;
	double _volatility;
	double _interest_rate;  
	double sum;
	double sum_squared; // used to calculate the variance for the confidence interval

public:
	//Declaration of the constructor with the parameters option, initial_price, interest_rate and volatility
	BlackScholesMCPricer(Option*, double, double, double);

	//Destructor
	~BlackScholesMCPricer();

	//Declaration of the function getNbPaths that returns the number of paths
	int getNbPaths(); 

	//Declaration of the function generate that generates nb_path paths
	void generate(int nb_paths);

	//Declaration of the function operator() that returns the price of the option with the paths generated
	double operator()();
	
	//Declaration of the function confidenceInterval that returns the confidence interval of the price of the option
	std::vector<double> confidenceInterval(); 
};

