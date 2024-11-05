#include "EuropeanDigitalPutOption.h"

EuropeanDigitalPutOption::EuropeanDigitalPutOption(double strike, double expiry) : EuropeanDigitalOption(expiry, strike) {
	_type = optionType::Put;
}

optionType EuropeanDigitalPutOption::GetOptionType() const {
	return _type;
}