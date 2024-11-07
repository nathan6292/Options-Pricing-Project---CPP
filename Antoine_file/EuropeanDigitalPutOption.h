#pragma once
#include "EuropeanDigitalOption.h"


class EuropeanDigitalPutOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalPutOption(double expiry, double strike)
        : EuropeanDigitalOption(expiry, strike) {
        type = OptionType::Put;
    }


    // Implémentation de la fonction payoff pour un digital put
    double payoff(double final_price) const override;
    OptionType GetOptionType() const override;
};
