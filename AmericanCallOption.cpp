#include "AmericanCallOption.h"

/// <summary>
/// Constructor for the AmericanCallOption class
/// </summary>
/// <param name="expiry">Maturity of the call</param>
/// <param name="strike">Strike of the option</param>
AmericanCallOption::AmericanCallOption(double expiry, double strike) : AmericanOption(expiry, strike) {
	_type = optionType::Call;
}

//Destructor for the AmericanCallOption class
AmericanCallOption::~AmericanCallOption() {}

/// <summary>
/// Computes the payoff of the American call optionat a given spot price
/// 
/// The payoff of a call option is the maximum between the spot price and the strike price
/// </summary>
/// <param name="spot">Asset Price</param>
/// <returns>Payoff of the american call at a given spot price</returns>
double AmericanCallOption::payoff(double spot) const {
	return std::max(spot - _strike, 0.0);
}

/// <summary>
/// Overriden function that returns the type of the option (Call)
/// </summary>
/// <returns>Returns call in this class</returns>
optionType AmericanCallOption::GetOptionType() const {
	return _type;
}
