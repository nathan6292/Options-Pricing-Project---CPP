#include "EuropeanDigitalPutOption.h"

/// <summary>
/// Constructor with the parameters expiry and strike
/// </summary>
/// <param name="expiry">Maturity of the option</param>
/// <param name="strike">Strike price of the option</param>
EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike) : EuropeanDigitalOption(expiry, strike) {
	_type = optionType::Put;
}

/// <summary>
/// Computes the payoff of the European digital put option at a given spot price
/// </summary>
/// <param name="spot">Price of the underlying asset</param>
/// <returns>Payoff of the EuropeanDigitalPutOption</returns>
double EuropeanDigitalPutOption::payoff(double spot) const {
	// If the spot price is less than or equal to the strike price, the payoff is 1, otherwise it is 0
	if (spot <= _strike)
		return 1;
	else
		return 0;
}

/// <summary>
/// Returns the type of the option (Put)
/// </summary>
/// <returns>Returns the type of the option</returns>
optionType EuropeanDigitalPutOption::GetOptionType() const {
	return _type;
}
