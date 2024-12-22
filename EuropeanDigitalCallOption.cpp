#include "EuropeanDigitalCallOption.h"

/// <summary>
/// Constructor with the parameters expiry and strike
/// </summary>
/// <param name="expiry">Maturity of the option</param>
/// <param name="strike">Strike price of the option</param>
EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike) : EuropeanDigitalOption(expiry, strike) {
	_type = optionType::Call;
}

/// <summary>
/// Computes the payoff of the European digital call option at a given spot price
/// 
/// The payoff of a European digital call option is 1 if the spot price is greater than or equal to the strike price, otherwise it is 0
/// </summary>
/// <param name="spot">Current price of the underlying asset</param>
/// <returns>0 if the spot price is less than the strike price, 1 otherwise</returns>
double EuropeanDigitalCallOption::payoff(double spot) const {
	if (spot >= _strike)
		return 1;
	else
		return 0;
}

/// <summary>
/// Returns the type of the option (Call)
/// </summary>
/// <returns>Call in this case</returns>
optionType EuropeanDigitalCallOption::GetOptionType() const {
	return _type;
}