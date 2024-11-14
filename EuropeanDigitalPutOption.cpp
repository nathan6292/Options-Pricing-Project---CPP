#include "EuropeanDigitalPutOption.h"

EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike) : EuropeanDigitalOption(expiry, strike) {
	_type = optionType::Put;
}