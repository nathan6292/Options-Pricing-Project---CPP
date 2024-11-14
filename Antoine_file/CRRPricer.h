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
    BinaryTree<bool> _exercise_policy;    // Arbre pour stocker la politique d'exercice

public:
    CRRPricer(option* option, int depth, double asset_price, double up, double down, double interest_rate);
          

    void compute();

    // Getter pour r�cup�rer la valeur dans l'arbre � un niveau et un indice donn�s
    double get(int level, int index)  { 
        return _tree.getNode(level, index);
    }

    // Getter pour la politique d'exercice (renvoie true si l'option doit �tre exerc�e au noeud donn�)
    bool getExercisePolicy(int level, int index)  {
        return _exercise_policy.getNode(level, index);
    }

    // Op�rateur() pour calculer le prix de l'option, avec un bool�en pour la forme ferm�e
    double operator()(bool closed_form = false);

};

#endif