#ifndef CRRPRICER_H
#define CRRPRICER_H

#include "BinaryTree.h"
#include "Option.h"
#include <cmath>
#include <stdexcept>



class CRRPricer {
private:
    option* _option;
    int _depth;
    double _asset_price, _up, _down, _interest_rate;
    BinaryTree<double> _tree;  // Arbre binaire pour stocker les valeurs de l'option

public:
    CRRPricer(option* option, int depth, double asset_price, double up, double down, double interest_rate);
          

    void compute();

    // Getter pour récupérer la valeur dans l'arbre à un niveau et un indice donnés
    double get(int level, int index)  { 
        return _tree.getNode(level, index);
    }


    // Opérateur() pour calculer le prix de l'option, avec un booléen pour la forme fermée
    double operator()(bool closed_form = false);

};

#endif