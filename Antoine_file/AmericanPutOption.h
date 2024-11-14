#pragma once
#include "AmericanOption.h"

class AmericanPutOption : public AmericanOption {
public:
    // Constructeur qui initialise la date d'échéance et le prix d'exercice
    AmericanPutOption(double expiry, double strike);

    // Calcul du payoff pour un Put américain
    double payoff(double S) const override;
};
