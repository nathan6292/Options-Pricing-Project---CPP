#include<iostream>
#include"CallOption.h"

CallOption::CallOption(double expiry, double strike) :EuropeanVanillaOption(expiry,strike)
{
	_type = optionType::Call;
}

optionType CallOption::GetOptionType()const
{
	return _type;
}