#include "CallOption.h"

/// <summary>
/// Constructor with the parameters expiry and strike
/// 
/// The constructor calls the constructor of the base class EuropeanVanillaOption with the parameters expiry and strike
///
/// Define the type of the option as a Call
/// </summary>
/// <param name="expiry">Expiration of the call</param>
/// <param name="strike">Strike of the call</param>
CallOption::CallOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {
	_type = optionType::Call;
}

/// <summary>
/// Returns the type of the option (Call in this case)
/// </summary>
/// <returns>type of the option (Call in this case)</returns>
optionType CallOption::GetOptionType() const {
	return _type;
}

/// <summary>
/// Computes the payoff of the call option
/// 
/// The payoff of a call option is the maximum between the spot price minus the strike and 0
/// </summary>
/// <param name="spot">Current spot price of the underlying asset</param>
/// <returns>Payoff of the call</returns>
double CallOption::payoff(double spot) const{
	return std::max(spot - _strike, 0.0);
}



