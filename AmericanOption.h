#pragma once
#include "option.h"

class AmericanOption : public option {
protected:
    double _expiry;
    double _strike;

    // Constructeur protégé pour les classes dérivées
    AmericanOption(double expiry, double strike);

public:
    // Méthode pour identifier une option américaine
    bool isAmericanOption() const override;
};
