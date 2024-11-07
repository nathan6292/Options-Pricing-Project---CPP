#pragma once
#include"option.h"
#include "OptionType.h"
#include <stdexcept> 

	
class EuropeanDigitalOption : public option
{
    
protected :
    OptionType type;
    double _strike;
public:
    EuropeanDigitalOption(double expiry, double strike) : option(expiry), _strike(strike) {
        if (expiry < 0 || strike < 0) {
            throw std::invalid_argument("Expiry and strike must be non-negative");
        }
    }

    virtual double payoff(double final_price) const = 0;

    virtual OptionType GetOptionType() const = 0;

    double getStrike() const {
        return _strike;
    }

    friend class BlackScholesPricer;

    // Déstructeur virtuel pour la gestion correcte de la mémoire
    virtual ~EuropeanDigitalOption() {}
};

