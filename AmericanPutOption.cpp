#include "AmericanPutOption.h"

/// <summary>
/// Constructor with the parameters expiry and strike
/// </summary>
/// <param name="expiry">Maturity of the option</param>
/// <param name="strike">Strike of the option</param>
AmericanPutOption::AmericanPutOption(double expiry, double strike) : AmericanOption(expiry, strike) {
	_type = optionType::Put;
}


//Destructor for the AmericanPutOption class
AmericanPutOption::~AmericanPutOption() {}

/// <summary>
/// Computes the payoff of the American put option at a given spot price
/// 
/// The payoff of a put option is the maximum between the strike price and the spot price
/// </summary>
/// <param name="spot">Price of the asset</param>
/// <returns>Payoff of the american put at a given spot price</returns>
double AmericanPutOption::payoff(double spot) const {
		return std::max(_strike - spot, 0.0);
}

/// <summary>
/// Overriden function that returns the type of the option (Put)
/// </summary>
/// <returns>Put in this case</returns>
optionType AmericanPutOption::GetOptionType() const {
	return _type;
}