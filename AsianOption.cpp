#include "AsianOption.h"
#include <stdexcept>

/// <summary>
/// Constructor for the AsianOption class
/// 
/// The constructor takes a vector of times as input and checks if the times are in increasing order and positive
/// </summary>
/// <param name="times">Vector of time_steps</param>
AsianOption::AsianOption(std::vector<double> times) : Option(times[times.size() - 1]) {
	// Check if the times are in increasing order and positive
	for (int i = 0; i < times.size() - 1; i++) {
		if (times[i] > times[i + 1])
			throw std::invalid_argument("Times must be in increasing order");
		if (times[i] < 0)
			throw std::invalid_argument("Time must be positive");
	}

	// Define the time steps
	time_steps = times; 
}

/// <summary>
/// Computes the payoff of the Asian option given a vector of spots at different times
/// 
/// The payoff of the Asian option is the payoff of a basic option with the price being the average of the spots at different times
/// 
/// The function payoff is defined in the derived classes call and put
/// </summary>
/// <param name="spots">Vectors with spots prices at different times</param>
/// <returns>Price of the Asian Option</returns>
double AsianOption::payoffPath(std::vector<double> spots) const{
	// Compute the mean of the spots
	double mean_spots = 0; 
	for (int i = 0; i < spots.size(); i++) {
		mean_spots += spots[i];
	}
	mean_spots = mean_spots / spots.size(); 

	// Return the payoff of the option with the mean of the spots depending on the type of the option
	return payoff(mean_spots);
}

/// <summary>
/// Return the time steps of the Asian option
/// </summary>
/// <returns>time_steps</returns>
std::vector<double> AsianOption::getTimeSteps() const {
	return time_steps;
}


/// <summary>
/// Returns true if the option is an Asian option
/// 
/// It is used to check if the option is an Asian option in the MC pricer
/// </summary>
/// <returns>True here and false in the base class Option</returns>
bool AsianOption::isAsianOption() const{
	return true; 
}
