#pragma once
#include "EuropeanVanillaOption.h"

class CallOption : public EuropeanVanillaOption
{
public : 
    // Constructeur qui appelle le constructeur de la classe de base
    CallOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {
        type = OptionType::Call;
    }

    // Implémentation de la fonction de paiement pour un call
    double payoff(double underlyingPrice) const override {
        return std::max(0.0, underlyingPrice - getStrike());
    }

    OptionType GetOptionType() const override;
};


