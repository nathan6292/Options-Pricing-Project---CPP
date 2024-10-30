#include "PutOption.h"

PutOption::PutOption(double strike, double expiry) : EuropeanVanillaOption(expiry, strike) {
	_type = optionType::Put;
}

optionType PutOption::GetOptionType() const {
	return _type;
}



