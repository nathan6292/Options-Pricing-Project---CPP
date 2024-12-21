#include "PutOption.h"

/// <summary>
/// Constructor with the parameters expiry and strike
/// 
/// The constructor calls the constructor of the base class EuropeanVanillaOption with the parameters expiry and strike
/// 
/// Define the type of the option as a Put
/// </summary>
/// <param name="expiry">Expiration of the put</param>
/// <param name="strike">Strike of the put</param>
PutOption::PutOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {
	_type = optionType::Put;
}

/// <summary>
/// Returns the type of the option (Put in this case)
/// </summary>
/// <returns>Type of the option (Put in this case)</returns>
optionType PutOption::GetOptionType() const {
	return _type;
}

/// <summary>
/// Computes the payoff of the put option
/// 
/// The payoff of a put option is the maximum between the strike minus the spot price and 0
/// </summary>
/// <param name="spot">Current spot price of the underlying asset</param>
/// <returns>Payoff of the put</returns>
double PutOption::payoff(double spot) const {
		return std::max(_strike - spot, 0.0);
}



