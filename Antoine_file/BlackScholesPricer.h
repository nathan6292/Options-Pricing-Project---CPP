#pragma once
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"
#include <cmath> //Pour pouvoir utiliser std::log etc...

#define M_PI 3.14159265358979323846 

class BlackScholesPricer
{
private:
    option* _option;
    double _assetPrice;
    double _interestRate;
    double _volatility;


public:

    BlackScholesPricer(option* option, double assetPrice,
        double interestRate, double volatility) : _option(option), _assetPrice(assetPrice), _interestRate(interestRate), _volatility(volatility) {}

    //permet de retrouver une valeur dans le tableau d'une loi normale centrée réduite
    double normalCDF(double value)const
    {
        return 0.5 * erfc(-value * std::sqrt(0.5));
    }

    double operator()() const {
        double T = _option->getExpiry();    // Expiry time
        double sigma = _volatility;         // Volatilité
        double r = _interestRate;           // Taux d'intérêt
        double S = _assetPrice;             // Prix de l'actif sous-jacent
        double K;// On va faire le getStrike pour une option vanille et digitale
        if (auto vanillaOption = dynamic_cast<EuropeanVanillaOption*>(_option)) {
            K = vanillaOption->getStrike(); 
        }
        else if (auto digitalOption = dynamic_cast<EuropeanDigitalOption*>(_option)) {
            K = digitalOption->getStrike(); 
        }
        else {
            // Gérer le cas où l'option n'est ni vanilla ni digitale
            return 0.0;
        }
        // Calcul de d1 et d2
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);

     
        if (auto digitalOption = dynamic_cast<EuropeanDigitalOption*>(_option)) {
            if (digitalOption->GetOptionType() == OptionType::Call) {
                return std::exp(-r * T) * normalCDF(d2);
            }
            else if (digitalOption->GetOptionType() == OptionType::Put) {
                return std::exp(-r * T) * normalCDF(-d2);
            }
        }
        // Sinon, calcul pour une option vanille
        else if (auto vanillaOption = dynamic_cast<EuropeanVanillaOption*>(_option)) {
            if (vanillaOption->GetOptionType() == OptionType::Call) {
                return S * normalCDF(d1) - K * std::exp(-r * T) * normalCDF(d2);
            }
            else if (vanillaOption->GetOptionType() == OptionType::Put) {
                return K * std::exp(-r * T) * normalCDF(-d2) - S * normalCDF(-d1);
            }
        }

        return 0.0; // Par défaut
    }

    double delta() const {
        double T = _option->getExpiry();
        double sigma = _volatility;
        double r = _interestRate;
        double S = _assetPrice;
        double K;
        if (auto vanillaOption = dynamic_cast<EuropeanVanillaOption*>(_option)) {
            K = vanillaOption->getStrike(); 
        }
        else if (auto digitalOption = dynamic_cast<EuropeanDigitalOption*>(_option)) {
            K = digitalOption->getStrike(); 
        }
        else {
            // Gérer le cas où l'option n'est ni vanilla ni digitale
            return 0.0;
        }

        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));

        // Si l'option est une option digitale
        if (auto digitalOption = dynamic_cast<EuropeanDigitalOption*>(_option)) {
            double d2 = d1 - sigma * std::sqrt(T);
            double nd2 = std::exp(-0.5 * d2 * d2) / std::sqrt(2 * M_PI);
            double factor = std::exp(-r * T) / (S * sigma * std::sqrt(T));
            return (digitalOption->GetOptionType() == OptionType::Call ? factor * nd2 : -factor * nd2);
        }
        // Sinon, delta pour une option vanille
        else if (auto vanillaOption = dynamic_cast<EuropeanVanillaOption*>(_option)) {
            if (vanillaOption->GetOptionType() == OptionType::Call) {
                return normalCDF(d1);
            }
            else if (vanillaOption->GetOptionType() == OptionType::Put) {
                return normalCDF(d1) - 1.0;
            }
        }

        return 0.0; // Par défaut
    }
};

