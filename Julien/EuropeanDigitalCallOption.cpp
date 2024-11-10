#include<iostream>
#include"EuropeanDigitalCallOption.h"

EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike) :EuropeanDigitalOption(expiry, strike)
{
	_type = optionType::Call;
}

optionType EuropeanDigitalCallOption::GetOptionType()const
{
	return _type;
}
