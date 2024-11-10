#include<iostream>
#include"EuropeanDigitalOption.h"
#include <stdexcept>

EuropeanDigitalOption::EuropeanDigitalOption(double expiry, double strike) : Option(expiry)
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

optionType EuropeanDigitalOption::GetOptionType() const
{
	return _type;
}

double EuropeanDigitalOption::payoff(double z)const
{
	if (_type == optionType::Call)
	{
		if (z >= _strike)
		{
			return 1;
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
			return 1;
		}
		else
		{
			return 0.0;
		}
	}
}
