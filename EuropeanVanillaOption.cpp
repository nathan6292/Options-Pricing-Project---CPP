#include "EuropeanVanillaOption.h"
#include <stdexcept>
#include <iostream> 

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

