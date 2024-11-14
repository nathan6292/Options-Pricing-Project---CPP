// Projet_c++_S7.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "BinaryTree.h"
#include "CallOption.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
#include "PutOption.h"
#include "BlackScholesPricer.h"
#include "CRRPricer.h"
#include "AsianOption.h"
#include "AsianCallOption.h"
#include "BlackScholesMCPricer.h"
#include "AmericanOption.h"
#include "AmericanCallOption.h"
#include <stdexcept>

int main()
{
     // Set depth of the tree

    /* Set values for the nodes
    tree.setNode(0, 0, 100.0);
    tree.setNode(1, 0, 110.0);
    tree.setNode(1, 1, 90.0);
    tree.setNode(2, 0, 121.0);
    tree.setNode(2, 1, 99.0);
    tree.setNode(2, 2, 81.0);
    tree.setNode(3, 0, 133.1);
    tree.setNode(3, 1, 108.9);
    tree.setNode(3, 2, 89.1);
    tree.setNode(3, 3, 72.9);

    // Display the tree
    tree.display();
    */

  //std::vector<double> observationDates = { 0.25, 0.5, 0.75, 1.0 };
  //EuropeanVanillaOption* call = new CallOption(5, 101);
    EuropeanVanillaOption* call = new CallOption(5, 101);
   
    // Paramètres pour le modèle de Black-Scholes
    double assetPrice = 100;  // Prix de l'actif sous-jacent
    double interestRate = 0.01;  // Taux d'intérêt
    double volatility = 0.1;     // Volatilité
    /*
    BlackScholesMCPricer pricer(call, assetPrice, interestRate, volatility); 
    pricer.generate(5000000);
    double estimated_price = pricer();
    std::vector<double> conf_interval = pricer.confidenceInterval();
    std::cout << "Prix de l'otion du call avec BSMC: " << estimated_price << std::endl;
    //std::cout << "95% Confidence Interval: [" << conf_interval[0] << ", " << conf_interval[1] << "]" << std::endl;
   
    BlackScholesPricer pricerr(call, assetPrice, interestRate, volatility);
    double pricee = pricerr();
    std::cout << "Prix de l'option call avec BS: " << pricee << std::endl;
    */
    
    double asset_price = 100;    // Prix actuel de l'actif
    double up = 0.05;              // Facteur de hausse
    double down = 0.045;            // Facteur de baisse
    double interest_rate = 0.01;  // Taux d'intérêt sans risque
    int depth = 5;
    BinaryTree<double> tree;

   

    BinaryTree<bool> exercise_policy;
   

    CRRPricer pricer(call, depth, asset_price, up, down, interest_rate);
    
    // Calcule le prix de l'option avec l'algorithme CRR (closed_form = false)
    double optionPriceCRR = pricer();
    std::cout << "Prix de l'option (CRR): " << optionPriceCRR << std::endl;
       

    return 0;

    
   
    /*
     //Calcul du Delta de l'option Call
    double delta = pricer.delta();
    std::cout << "Delta de l'option Call: " << delta << std::endl;
    

    // Libération de la mémoire
    delete putdigitalOption;
    */


}


