#pragma once
#include "Option.h"
#include "MT.h" // Assuming MT singleton is already implemented
#include <vector>
#include <stdexcept>
#include <cmath>

class BlackScholesMCPricer
{
private:
    option* _option;
    double _initial_price;
    double _interest_rate;
    double _volatility;
    int _nb_paths;
    double _price_estimate;
    double _sum_squared; // To track variance for confidence interval calculation
public : 
    BlackScholesMCPricer(option* option, double initial_price, double interest_rate, double volatility)
        : _option(option), _initial_price(initial_price), _interest_rate(interest_rate),
        _volatility(volatility), _nb_paths(0), _price_estimate(0.0), _sum_squared(0.0) {}

    // Getter for the number of paths generated
    int getNbPaths() const { return _nb_paths; }

    // Generate paths and update the price estimate
    void generate(int nb_paths);

    // Overload operator() to return the current price estimate
    double operator()() const;

    // Method to compute the 95% confidence interval
    std::vector<double> confidenceInterval() const;
};

