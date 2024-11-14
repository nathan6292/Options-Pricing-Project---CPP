#pragma once
#include "AmericanOption.h"

class AmericanCallOption : public AmericanOption {
public:
    // Constructeur qui initialise la date d'�ch�ance et le prix d'exercice
    AmericanCallOption(double expiry, double strike);

    // Calcul du payoff pour un Call am�ricain
    double payoff(double S) const override;
};
