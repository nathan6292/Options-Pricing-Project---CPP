#pragma once
#include "option.h"
#include "OptionType.h"
#include <stdexcept> // Pour gérer les exceptions avec std::invalid_argument


class EuropeanVanillaOption : public option
{
private :
    double _strike;

protected :
    OptionType  type;

public :
    // Constructeur qui initialise _expiry et _strike avec des arguments
    EuropeanVanillaOption(double, double);

    // Getter pour le strike
    double getStrike() const {
        return _strike;
    }

    virtual double payoff(double final_price) const = 0;

    virtual OptionType GetOptionType() const = 0;

    // Déstructeur virtuel pour la gestion correcte de la mémoire
    virtual ~EuropeanVanillaOption() {}

    friend class BlackScholesPricer;
};

