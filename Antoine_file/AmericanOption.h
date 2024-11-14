#pragma once
#include "option.h"

class AmericanOption : public option {
protected:
    double _expiry;
    double _strike;

    // Constructeur prot�g� pour les classes d�riv�es
    AmericanOption(double expiry, double strike);

public:
    // M�thode pour identifier une option am�ricaine
    bool isAmericanOption() const override;
};
