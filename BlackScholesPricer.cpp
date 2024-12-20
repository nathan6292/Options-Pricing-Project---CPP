#include "BlackScholesPricer.h"
#include <cmath>
#include <iostream>

BlackScholesPricer::BlackScholesPricer(EuropeanVanillaOption* option, double asset_price, double interest_rate, double volatility)
	: _option_vanilla(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility),_option_digital(nullptr) {}

BlackScholesPricer::BlackScholesPricer(EuropeanDigitalOption* option, double asset_price, double interest_rate, double volatility)
    : _option_digital(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility), _option_vanilla(nullptr) {}

double BlackScholesPricer::operator()() const {
    double S = _asset_price;
    double r = _interest_rate;
    double sigma = _volatility;
    if (_option_vanilla != nullptr) {
        double T = _option_vanilla->getExpiry();
        double K = (*_option_vanilla)._strike;
        

        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);

        if ((*_option_vanilla).GetOptionType() == optionType::Call)
            return S * 0.5 * std::erfc(-d1 / std::sqrt(2)) - K * std::exp(-r * T) * 0.5 * std::erfc(-d2 / std::sqrt(2));
        else
            return -S * 0.5 * std::erfc(d1 / std::sqrt(2)) + K * std::exp(-r * T) * 0.5 * std::erfc(d2 / std::sqrt(2));
    }
    else {
        double T = _option_digital->getExpiry();
        double K = _option_digital->_strike;
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);

        if ((*_option_digital).GetOptionType() == optionType::Call) {
            return std::exp(-r * T) * 0.5 * std::erfc(-d2 / std::sqrt(2));
        }
        else {
            return std::exp(-r * T) * 0.5 * std::erfc(d2 / std::sqrt(2));
        }
    }
}

double BlackScholesPricer::delta() const {
        double S = _asset_price;
        double r = _interest_rate;
        double sigma = _volatility;

		if (_option_vanilla != nullptr) {
            double T = _option_vanilla->getExpiry();
            double K = (*_option_vanilla)._strike;
            double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));

            if ((*_option_vanilla).GetOptionType() == optionType::Call)
                return 0.5 * std::erfc  (-d1 / std::sqrt(2));
            else
                return 0.5 * std::erfc(-d1 / std::sqrt(2)) - 1;
        }
        else{
	        double T = _option_digital->getExpiry();
	        double K = _option_digital->_strike;
	        double d2 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T)) - sigma*std::sqrt(T);
            double delta = (std::exp(-r * T) / (S * sigma * std::sqrt(2 * 3.14159265358979323846 * T))) * std::exp(-d2 * d2 / 2);
	        if ((*_option_digital).GetOptionType() == optionType::Call)
		        return delta;
	        else
		        return -delta;
        }
}