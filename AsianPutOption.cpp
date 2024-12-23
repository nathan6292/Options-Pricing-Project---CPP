#include "AsianPutOption.h"
#include <stdexcept>

/// <summary>
/// Constructor with the parameters times and strike
/// </summary>
/// <param name="times">Vector with all times_steps</param>
/// <param name="strike">Strike of the option</param>
AsianPutOption::AsianPutOption(std::vector<double> times, double strike) : AsianOption(times) {
	// Check if the strike is positive
	if (strike < 0)
		throw std::invalid_argument("Strike must be positive");

	_strike = strike;

	// Set the type of the option to put
	_type = optionType::Put;
}

//Destructor for the AsianPutOption class
AsianPutOption::~AsianPutOption() {}

/// <summary>
/// Computes the payoff of the Asian Put option at a given mean spot price 
/// 
/// The payoff of a put option is the maximum between the mean spot price and the strike price
/// 
/// This function is used by the payoffPath function in the Asian Option class to compute the final payoff of the Asian option
/// </summary>
/// <param name="mean_spot">Mean of spot prices from the beginning to the maturity of the option</param>
/// <returns>Returns the payoff of the option depending the mean of the spot prices during the life of the option</returns>
double AsianPutOption::payoff(double mean_spot) const {
	return std::max(_strike - mean_spot, 0.0);
}
