#pragma once
#include "AmericanOption.h"

class AmericanPutOption : public AmericanOption {
public:
    // Constructeur qui initialise la date d'�ch�ance et le prix d'exercice
    AmericanPutOption(double expiry, double strike);

    // Calcul du payoff pour un Put am�ricain
    double payoff(double S) const override;
};
