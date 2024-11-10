#include<iostream>
#include"BlackScholesPricer.h"
#define M_PI 3.14159265358979323846 


double BlackScholesPricer::normal_pdf(double x)const
{
	return (1.0 / std::sqrt(2 * M_PI)) * std::exp(-0.5 * x * x);
}

BlackScholesPricer::BlackScholesPricer(Option* option, double asset_price, double interest_rate, double volatility)
	:_option(option),_asset_price(asset_price),_interest_rate(interest_rate),_volatility(volatility){}

double BlackScholesPricer::operator()() const //voir wikipedia
{
	if (EuropeanVanillaOption* option = dynamic_cast<EuropeanVanillaOption*>(_option))
	{
		double strike = (*option)._strike; // Accès au strike via l'option
		double expiry = _option->getExpiry(); // Accès à l'expiry via la méthode

		double d1 = (1 / (_volatility * sqrt(expiry))) * (log(_asset_price / strike) + (_interest_rate + 0.5 * _volatility * _volatility) * expiry);
		double d2 = d1 - _volatility * sqrt(expiry);

		if ((*option)._type == optionType::Call)
			return _asset_price * 0.5 * std::erfc(-d1 / std::sqrt(2)) - strike * std::exp(-_interest_rate * expiry) * 0.5 * std::erfc(-d2 / std::sqrt(2));
		else if ((*option)._type == optionType::Put)
			return -_asset_price * 0.5 * std::erfc(d1 / std::sqrtf(2)) + strike * std::exp(-_interest_rate * expiry) * 0.5 * std::erfc(d2 / std::sqrt(2));

	}

	else if (EuropeanDigitalOption* option = dynamic_cast<EuropeanDigitalOption*>(_option))
	{
		double strike = (*option)._strike; // Accès au strike via l'option
		double expiry = _option->getExpiry(); // Accès à l'expiry via la méthode

		double d1 = (1 / (_volatility * sqrt(expiry))) * (log(_asset_price / strike) + (_interest_rate + 0.5 * _volatility * _volatility) * expiry);
		double d2 = d1 - _volatility * sqrt(expiry);

		if ((*option)._type == optionType::Call)
			return exp(-_interest_rate * expiry) * 0.5 * erfc(-d2 / sqrt(2));
		else if ((*option)._type == optionType::Put)
			return exp(-_interest_rate * expiry) * 0.5 * erfc(d2 / sqrt(2));
	}
}

double BlackScholesPricer::delta()const
{
	if (EuropeanVanillaOption* option = dynamic_cast<EuropeanVanillaOption*>(_option))
	{
		double strike = (*option)._strike; // Accès au strike via l'option
		double expiry = _option->getExpiry(); // Accès à l'expiry via la méthode

		double d1 = (1 / (_volatility * sqrt(expiry))) * (log(_asset_price / strike) + (_interest_rate + 0.5 * _volatility * _volatility) * expiry); //obligé de redefinir d1 et d'utiliser le pointeur pour expiry
		if ((*option)._type == optionType::Call)
			return std::erfc(d1);
		else
			return std::erfc(d1) - 1;
	}

	else if (EuropeanDigitalOption* option = dynamic_cast<EuropeanDigitalOption*>(_option))
	{
		double strike = (*option)._strike; // Accès au strike via l'option
		double expiry = _option->getExpiry(); // Accès à l'expiry via la méthode

		double d1 = (1 / (_volatility * sqrt(expiry))) * (log(_asset_price / strike) + (_interest_rate + 0.5 * _volatility * _volatility) * expiry);
		double d2 = d1 - _volatility * sqrt(expiry);

		return exp(-_interest_rate * expiry) * normal_pdf(d2) / (_volatility * _asset_price * sqrt(expiry));
	}
}
