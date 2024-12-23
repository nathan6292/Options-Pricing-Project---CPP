#include "BlackScholesPricer.h"
#include <cmath>
#include <iostream>

/// <summary>
/// Constructor with the parameters option, asset_price, interest_rate and volatility for an EuropeanVanillaOption
/// 
/// The constructor initializes the private variables _option_vanilla, _asset_price, _interest_rate and _volatility
/// 
/// The constructor initializes the private variable _option_digital to nullptr because the option is an EuropeanVanillaOption
/// </summary>
/// <param name="option">Pointer to an EuropeanVanillaOption</param>
/// <param name="asset_price">Current spot price of the underlying asset</param>
/// <param name="interest_rate">Risk-free interest rate</param>
/// <param name="volatility">Volatility of the underlying asset</param>
BlackScholesPricer::BlackScholesPricer(EuropeanVanillaOption* option, double asset_price, double interest_rate, double volatility)
	: _option_vanilla(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility),_option_digital(nullptr) {}


/// <summary>
/// Constructor with the parameters option, asset_price, interest_rate and volatility for an DigitalVanillaOption
/// 
/// The constructor initializes the private variables _option_digital, _asset_price, _interest_rate and _volatility
/// 
/// The constructor initializes the private variable _option_vanilla to nullptr because the option is an EuropeanDigitalOption
/// </summary>
/// <param name="option">Pointer to an EuropeanDigitalOption</param>
/// <param name="asset_price">Current spot price of the underlying asset</param>
/// <param name="interest_rate">Risk-free interest rate</param>
/// <param name="volatility">Volatility of the underlying asset</param>
BlackScholesPricer::BlackScholesPricer(EuropeanDigitalOption* option, double asset_price, double interest_rate, double volatility)
    : _option_digital(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility), _option_vanilla(nullptr) {}

//Destructor
BlackScholesPricer::~BlackScholesPricer() {}

/// <summary>
/// Computes the price of the option
/// 
/// The price of the option is computed using the Black-Scholes formula
/// </summary>
/// <returns>Price of the option</returns>
double BlackScholesPricer::operator()() const {
	// Declare the variables S, r, sigma
    double S = _asset_price;
    double r = _interest_rate;
    double sigma = _volatility;

	// If the option is an EuropeanVanillaOption
    if (_option_vanilla != nullptr) {
		// Declare the variables T, K, d1, d2 using the Black-Scholes formula
        double T = _option_vanilla->getExpiry();
        double K = (*_option_vanilla)._strike;
        

        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);

		// If the option is a Call
        if ((*_option_vanilla).GetOptionType() == optionType::Call)
			// Return the price of the Vanilla Call option using the Black-Scholes formula
            return S * 0.5 * std::erfc(-d1 / std::sqrt(2)) - K * std::exp(-r * T) * 0.5 * std::erfc(-d2 / std::sqrt(2));
		// If the option is a Put
        else
			// Return the price of the Vanilla Put option using the Black-Scholes formula
            return -S * 0.5 * std::erfc(d1 / std::sqrt(2)) + K * std::exp(-r * T) * 0.5 * std::erfc(d2 / std::sqrt(2));
    }
	// If the option is an EuropeanDigitalOption
    else {
		// Declare the variables T, K, d1, d2 using the Black-Scholes formula
        double T = _option_digital->getExpiry();
        double K = _option_digital->_strike;
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);

		// If the option is a Call
        if ((*_option_digital).GetOptionType() == optionType::Call) {
			// Return the price of the Digital Call option using the Black-Scholes formula
            return std::exp(-r * T) * 0.5 * std::erfc(-d2 / std::sqrt(2));
        }
        else {
			// Return the price of the Digital Put option using the Black-Scholes formula
            return std::exp(-r * T) * 0.5 * std::erfc(d2 / std::sqrt(2));
        }
    }
}

/// <summary>
/// Computes the delta of the option (derivative of the price with respect to the asset price)
/// 
/// The delta of the option is computed using the Black-Scholes formula
/// 
/// The delta is the variation of the price of the option with respect to the asset price
/// </summary>
/// <returns>Delta of the option</returns>
double BlackScholesPricer::delta() const {
	// Declare the variables S, r, sigma
        double S = _asset_price;
        double r = _interest_rate;
        double sigma = _volatility;

		// If the option is an EuropeanVanillaOption
		if (_option_vanilla != nullptr) {
			// Declare the variables T, K, d1 using the Black-Scholes formula
            double T = _option_vanilla->getExpiry();
            double K = (*_option_vanilla)._strike;
            double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));

			// If the option is a Call
            if ((*_option_vanilla).GetOptionType() == optionType::Call)
				// Return the delta of the Vanilla Call option using the Black-Scholes formula
                return 0.5 * std::erfc  (-d1 / std::sqrt(2));
            else
				// Return the delta of the Vanilla Put option using the Black-Scholes formula
                return 0.5 * std::erfc(-d1 / std::sqrt(2)) - 1;
        }
		// If the option is an EuropeanDigitalOption
        else{
			// Declare the variables T, K, d2 using the Black-Scholes formula
	        double T = _option_digital->getExpiry();
	        double K = _option_digital->_strike;
	        double d2 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T)) - sigma*std::sqrt(T);

			// Declare the variable delta using the Black-Scholes formula for the Digital option 
            double delta = (std::exp(-r * T) / (S * sigma * std::sqrt(2 * 3.141592 * T))) * std::exp(-d2 * d2 / 2);

			// If the option is a Call
	        if ((*_option_digital).GetOptionType() == optionType::Call)
		        return delta;
			// If the option is a Put
	        else
		        return -delta;
        }
}