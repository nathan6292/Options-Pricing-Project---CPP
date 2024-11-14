#pragma once
#include "AmericanOption.h"

class AmericanCallOption : public AmericanOption {
public:
    // Constructeur qui initialise la date d'échéance et le prix d'exercice
    AmericanCallOption(double expiry, double strike);

    // Calcul du payoff pour un Call américain
    double payoff(double S) const override;
};
