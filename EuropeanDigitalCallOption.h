#pragma once
#include "EuropeanDigitalOption.h"

class EuropeanDigitalCallOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalCallOption(double expiry, double strike): EuropeanDigitalOption(expiry, strike) 
    {
        type = OptionType::Call;
    }

    // Implémentation de la fonction payoff pour un digital call
    double payoff(double final_price) const override;

    OptionType GetOptionType() const override;
};


