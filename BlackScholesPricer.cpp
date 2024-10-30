#include "BlackScholesPricer.h"
#include <cmath>
#include <iostream>

BlackScholesPricer::BlackScholesPricer(EuropeanVanillaOption* option, double asset_price, double interest_rate, double volatility)
	: _option(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility) {}

double BlackScholesPricer::operator()() const {

    double T = _option->getExpiry();
    double K = (*_option)._strike;
    double S = _asset_price;
    double r = _interest_rate;
    double sigma = _volatility;

    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

	std::cout << "d1: " << d1 << std::endl;

    if ((*_option)._type == optionType::Call)
        return S * 0.5 * std::erfc(-d1/std::sqrt(2)) - K * std::exp(-r * T) * 0.5 * std::erfc(-d2 / std::sqrt(2));
    else
        return K * std::exp(-r * T) * 0.5 * std::erfc(d2 / std::sqrt(2)) - S * 0.5 * std::erfc(-d1 / std::sqrt(2));
}

double BlackScholesPricer::delta() const {
	double d1 = (1 / (_volatility * sqrt(_option->getExpiry()) * (log(_asset_price / (*_option)._strike) + (_interest_rate + pow(_volatility, 2) / 2) * _option->getExpiry())));
	if ((*_option)._type == optionType::Call)
		return std::erfc(d1);
	else
		return std::erfc(d1) - 1;
}