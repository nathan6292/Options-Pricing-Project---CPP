#include "AmericanPutOption.h"

AmericanPutOption::AmericanPutOption(double expiry, double strike) : AmericanOption(expiry, strike) {
	_type = optionType::Put;
}