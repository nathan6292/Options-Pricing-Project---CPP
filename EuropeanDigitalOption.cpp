#include "EuropeanDigitalOption.h"
#include <stdexcept>

/// <summary>
/// Constructor with the parameters expiry and strike
/// </summary>
/// <param name="expiry">Maturity of the option</param>
/// <param name="strike">Strike price of the option</param>
EuropeanDigitalOption::EuropeanDigitalOption(double expiry, double strike) : Option(expiry) {
	// Check if the expiry and strike are positive
	if (expiry < 0)
		throw std::invalid_argument("Expiry must be positive");
	if (strike < 0)
		throw std::invalid_argument("Strike must be positive");

	_strike = strike;
}

// Destructor for the EuropeanDigitalOption class
EuropeanDigitalOption::~EuropeanDigitalOption() {}

