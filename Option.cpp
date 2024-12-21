#include "Option.h"

/// <summary>
/// Constructor with the parameter expiry
/// </summary>
/// <param name="expiry">Expiry of the option</param>
Option::Option(double expiry) : _expiry(expiry) {}

/// <summary>
/// returns the expiry of the option
/// </summary>
/// <returns>Expiry of the option</returns>
double Option::getExpiry() const {
	return _expiry;
}

/// <summary>
/// returns the payoff using the path for Asian options
/// </summary>
/// <param name="time">Vector of time steps for the path of the Asian option</param>
/// <returns>Payoff of the Asian option</returns>
double Option::payoffPath(std::vector<double> time) const {
	return payoff(time[time.size() - 1]);
}


/// <summary>
/// Check if the option is an Asian option
/// The non-overriden function returns false by default and is overriden in the AsianOption class
/// </summary>
/// <returns>returns false in the non-overriden function</returns>
bool Option::isAsianOption() const{
	return false; 
}

/// <summary>
/// Check if the option is an American option
/// The non-overriden function returns false by default and is overriden in the AmericanOption class
/// </summary>
/// <returns>returns false in the non-overriden function</returns>
bool Option::isAmericanOption() const {
	return false; 
}


