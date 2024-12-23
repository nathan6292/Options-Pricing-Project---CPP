#include "Option.h"

/// <summary>
/// Constructor with the parameter expiry
/// </summary>
/// <param name="expiry">Expiry of the option</param>
Option::Option(double expiry) : _expiry(expiry) {}


//Destructor for the Option class
Option::~Option() {}

/// <summary>
/// returns the expiry of the option
/// </summary>
/// <returns>Expiry of the option</returns>
double Option::getExpiry() const {
	return _expiry;
}

/// <summary>
/// returns the payoff using the path for Asian options
/// 
/// The payoff of the Asian option is the payoff of a basic option with the price being the average of the spots at different times
/// Here, the base class Option returns the payoff of the option at the last time step like a basic option
/// 
/// The payoff of the Asian option is defined in the derived classes AsianOption
/// </summary>
/// <param name="time">Vector of the price at different time steps for the Asian option</param>
/// <returns>Payoff of the option</returns>
double Option::payoffPath(std::vector<double>& time) const {
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


