// Projet_c++_S7.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "BinaryTree.h"
#include "CallOption.h"
#include "PutOption.h"
#include "BlackScholesPricer.h"
#include "CRRPricer.h"
int main()
{
    BinaryTree<double> tree;

    tree.setDepth(3);  // Set depth of the tree

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

   EuropeanVanillaOption* callOption = new CallOption(.1,100);

    // Paramètres pour le modèle de Black-Scholes
    double assetPrice = 110.0;  // Prix de l'actif sous-jacent
    double interestRate = 0.05;  // Taux d'intérêt
    double volatility = 0.6;     // Volatilité

    BlackScholesPricer price(callOption, assetPrice, interestRate, volatility);

    double asset_price = 50.0;    // Prix actuel de l'actif
    double up = 1.1;              // Facteur de hausse
    double down = 0.9;            // Facteur de baisse
    double interest_rate = 0.95;  // Taux d'intérêt sans risque
    int depth = 3;

    CRRPricer pricer(callOption, depth, asset_price, up, down, interest_rate);

    // Calcule le prix de l'option avec l'algorithme CRR (closed_form = false)
    double optionPriceCRR = pricer(false);
    std::cout << "Prix de l'option (CRR): " << optionPriceCRR << std::endl;

    // Affichage de toutes les valeurs dans l'arbre
    std::cout << "Arbre des valeurs de l'option :" << std::endl;
    for (int n = 0; n <= depth; ++n) {
        for (int i = 0; i <= n; ++i) {
            std::cout << "H(" << n << ", " << i << ") = " << pricer.get(n, i) << " ";
        }
        std::cout << std::endl;  // Nouvelle ligne pour chaque niveau
    }


    return 0;

    /*
    // Calcul du prix de l'option Call
    double price = pricer();
    std::cout << "Prix de l'option Call: " << price << std::endl;

    // Calcul du Delta de l'option Call
    double delta = pricer.delta();
    std::cout << "Delta de l'option Call: " << delta << std::endl;

    // Libération de la mémoire
    delete callOption;
    */


}


