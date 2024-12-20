#include "EuropeanDigitalOption.h"
#include <stdexcept>

EuropeanDigitalOption::EuropeanDigitalOption(double expiry, double strike) : Option(expiry) {
	if (expiry < 0)
		throw std::invalid_argument("Expiry must be positive");
	if (strike < 0)
		throw std::invalid_argument("Strike must be positive");

	_strike = strike;
}

