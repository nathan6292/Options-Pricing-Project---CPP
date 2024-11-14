#pragma once
#include "EuropeanVanillaOption.h"

class PutOption : public EuropeanVanillaOption
{
public : 
    // Constructeur qui appelle le constructeur de la classe de base
    PutOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {
        type = OptionType:: Put;
    }

    // Implémentation de la fonction de paiement pour un put
    // h(z) = max(K - z, 0)
    double payoff(double underlyingPrice) const override {
        return std::max(0.0, getStrike() - underlyingPrice);
    }

    OptionType GetOptionType() const override;
};

