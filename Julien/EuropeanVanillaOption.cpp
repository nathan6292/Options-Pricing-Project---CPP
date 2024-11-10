#include<iostream>
#include"EuropeanVanillaOption.h"
#include <stdexcept>

EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike) : Option (expiry)
{
	if (expiry < 0)
	{
		throw std::invalid_argument("expiry must be positive");
	}

	if (strike < 0)
	{
		throw std::invalid_argument("strike must be positive");
	}

	_strike = strike;
}

optionType EuropeanVanillaOption::GetOptionType() const
{
	return _type;
}

double EuropeanVanillaOption::payoff(double z)const
{
	if (_type==optionType::Call)
	{
		if (z >= _strike)
		{
			return z - _strike;
		}
		else
		{
			return 0.0;
		}
	}

	else
	{
		if (_strike >= z)
		{
			return _strike - z;
		}
		else
		{
			return 0.0;
		}
	}
}
