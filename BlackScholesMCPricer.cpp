#include "BlackScholesMCPricer.h"
#include <cmath>
#include <iostream>
#include <stdexcept>


/// <summary>
/// Constructor of the class BlackScholesMCPricer
/// 
/// The constructor initializes the pricer with the option, the initial price, the interest rate and the volatility
/// </summary>
/// <param name="option">Option that we want to price</param>
/// <param name="initial_price">Price of the asset at t=0 (now)</param>
/// <param name="interest_rate">Interest_rate</param>
/// <param name="volatility">Volatility of the asset</param>
BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility) {
	_option = option;
	_initial_price = initial_price; 
	_interest_rate = interest_rate;
	_volatility = volatility; 
	npaths = 0; 
	sum = 0;
	sum_squared = 0;
}

// Returns the number of paths generated
int BlackScholesMCPricer::getNbPaths() {
	return npaths; 
}

/// <summary>
/// Generates nb_paths paths and computes the sum of the payoffs and the sum of the squared payoffs
/// 
/// It uses the Black-Scholes formula to generate the paths and the MT class to generate
/// </summary>
/// <param name="nb_paths">Number of paths that we want to generate</param>
void BlackScholesMCPricer::generate(int nb_paths) {

	// Compute the discount factor for the Asian option in order to avoid recomputing exponential at each time step
	double discount_factor = std::exp(-_interest_rate * (*_option).getExpiry());

	// Check if the option is an Asian option
	if ((*_option).isAsianOption()) {
		// Cast the option to an AsianOption
		AsianOption* option = dynamic_cast<AsianOption*>(_option);

		// Get the time steps of the option
		std::vector<double> time_steps = (*option).getTimeSteps();

		// Initialize the vector path that will contain the prices of the asset at each time step
		std::vector<double> path(time_steps.size(), 0);

		//Generate nb_paths paths
		for(int i = 0; i < nb_paths; i++) {
			//Reset the path to 0
			for (size_t i = 0; i < path.size(); ++i) {
				path[i] = 0;
			}
	
			// Set the first price of the path to the initial price
			path[0] = _initial_price;

			// Initialize a temporary variable to store the last price generated in the path
			double price = _initial_price;

			//Generate the prices of the asset at each time step
			for (int j = 1; j < time_steps.size(); j++) {
				//Compute time between two time steps
				double dt = time_steps[j] - time_steps[j - 1];

				//Compute the drift, which is the interest rate minus half the volatility squared
				double drift = (_interest_rate - (_volatility * _volatility) / 2) * dt;

				//Compute the diffusion, which is the volatility times the square root of the time step times a random number
				double diffusion = _volatility * std::sqrt(dt) * MT::rand_norm();

				// Generate the price of the asset at time step 
				price *=std::exp(drift + diffusion);
				// Store the price in the path vector
				path[j] = price;
			}
		
			// Compute the payoff of the Asian option with the path generated
			double pay = (*option).payoffPath(path)*discount_factor;

			// Update the sum of the payoffs and the sum of the squared payoffs;
			sum += pay;
			sum_squared += pay*pay;

			// Increment the number of paths generated
			npaths++;
		}
	}

	// If the option is not an Asian option
	else {
		// Generate nb_paths prices of the asset (we don't need to store the paths because we only need the price of the option at maturity)
			for (int i = 0; i < nb_paths; i++) {
				// Generate the price of the asset at maturity
				double pay = discount_factor*(*_option).payoff(_initial_price * std::exp((_interest_rate - (_volatility * _volatility) / 2) * ((*_option).getExpiry()) + _volatility * std::sqrt((*_option).getExpiry()) * MT::rand_norm()));

				// Update the sum of the payoffs and the sum of the squared payoffs
				sum += pay;
				sum_squared += pay * pay;

				// Increment the number of paths generated
				npaths++;
			}
	}
}

/// <summary>
/// Computes the price of the option using the Monte Carlo method
/// </summary>
/// <returns>Price of the Asian or European option</returns>
double BlackScholesMCPricer::operator()() {
	// Check if we have generated paths/price
		if (npaths == 0) {
			throw std::invalid_argument("Zero paths generated : use the generate function before calling the operator");
		}

		// Return the average of the payoffs discounted at the interest rate
		return (sum /npaths);
}

/// <summary>
/// Computes the confidence interval of the price of the option using the Monte Carlo method
/// 
/// The confidence interval is computed using the formula : mean +/- 1.96 * std_dev/sqrt(npaths)
/// </summary>
/// <returns></returns>
std::vector<double> BlackScholesMCPricer::confidenceInterval() {
	// Check if we have generated paths/price
	if (npaths == 0) {
		throw std::invalid_argument("Zero paths generated : use the generate function before calling the confidenceInterval");
	}

	// Compute the mean of the payoffs
	double mean = (sum / npaths);

	// Compute the standard deviation of the payoffs
	double std_dev = std::sqrt(sum_squared / npaths - mean * mean);

	// Compute the confidence interval
	double half_length = 1.96 * std_dev / std::sqrt(npaths);

	// Return the confidence interval
	return { mean - half_length, mean + half_length };
}