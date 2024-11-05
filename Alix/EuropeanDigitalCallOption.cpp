#include "EuropeanDigitalOption.h"

Option::EuropeanDigitalEuropeanDigitalOption(double expiry) : _expiry(expiry) {}

double Option::getExpiry() const {
	return _expiry;
}