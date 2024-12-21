#include "EuropeanVanillaOption.h"
#include <stdexcept>
#include <iostream> 

/// <summary>
/// Contructor with the parameters expiry and strike
/// The constructor calls the constructor of the base class Option with the parameter expiry
/// 
/// Check if the expiry and the strike are nonnegative
/// If not, throw an exception
/// 
/// Set the strike to the value of the parameter strike
/// </summary>
/// <param name="expiry">expiry of the option</param>
/// <param name="strike">strike of the option</param>
EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike) : Option(expiry) {
    try {
        if (expiry < 0)
            throw std::invalid_argument("Expiry must be positive");
        if (strike < 0)
            throw std::invalid_argument("Strike must be positive");
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        std::abort();
    }

	_strike = strike;
}

