#include "BlackScholesPricer.h"
#include <cmath>
#include <iostream>

BlackScholesPricer::BlackScholesPricer(Option* option, double asset_price, double interest_rate, double volatility)
	: _option(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility) {}

double BlackScholesPricer::operator()() const {
    if (EuropeanVanillaOption* option = dynamic_cast<EuropeanVanillaOption*>(_option)) {
        double T = option->getExpiry();
        double K = (*option)._strike;
        double S = _asset_price;
        double r = _interest_rate;
        double sigma = _volatility;

        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);

        if ((*option)._type == optionType::Call)
            return S * 0.5 * std::erfc(-d1 / std::sqrt(2)) - K * std::exp(-r * T) * 0.5 * std::erfc(-d2 / std::sqrt(2));
        else
            return -S * 0.5 * std::erfc(d1 / std::sqrt(2)) + K * std::exp(-r * T) * 0.5 * std::erfc(d2 / std::sqrt(2));
    }
    else if (EuropeanDigitalOption* option = dynamic_cast<EuropeanDigitalOption*>(_option)) {
        double T = option->getExpiry();
        double K = (*option)._strike;
        double S = _asset_price;
        double r = _interest_rate;
        double sigma = _volatility;
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);

        if ((*option)._type == optionType::Call) {
            return std::exp(-r * T) * 0.5 * std::erfc(-d2 / std::sqrt(2));
        }
        else {
            return std::exp(-r * T) * 0.5 * std::erfc(d2 / std::sqrt(2));
        }
    }
}


double BlackScholesPricer::delta() const {
    if (typeid(*_option) == typeid(EuropeanVanillaOption)) {
        EuropeanVanillaOption* option = static_cast<EuropeanVanillaOption*>(_option);

        double d1 = (1 / (_volatility * sqrt(_option->getExpiry()) * (log(_asset_price / (*option)._strike) + (_interest_rate + pow(_volatility, 2) / 2) * _option->getExpiry())));
        if ((*option)._type == optionType::Call)
            return std::erfc(d1);
        else
            return std::erfc(d1) - 1;
    }
}