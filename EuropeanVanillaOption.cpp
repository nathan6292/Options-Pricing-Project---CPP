#include "EuropeanVanillaOption.h"
#include <stdexcept>

EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike) : option(expiry), _strike(strike) {
    // V�rifier que l'expiration et le strike sont non-n�gatifs
    if (expiry < 0 || strike < 0) {
        throw std::invalid_argument("Expiry and strike must be non-negative");
    }
    _strike = strike;
}




