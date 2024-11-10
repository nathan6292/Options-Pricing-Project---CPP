#pragma once
#include<iostream>
#include <cmath>
#include"EuropeanVanillaOption.h"
#include"EuropeanDigitalOption.h"

class BlackScholesPricer
{
public:
	BlackScholesPricer(Option*, double, double, double);
    double operator()() const;
    double delta() const;
    double normal_pdf(double)const; //const pour pouvoir l'appeller dans la méthode delta qui est const
private:
    Option* _option; // Pointeur vers l'option
    double _asset_price; // Prix de l'actif sous-jacent
    double _interest_rate; // Taux d'intérêt
    double _volatility; // Volatilité de l'actif
};
