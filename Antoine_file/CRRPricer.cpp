#include "CRRPricer.h"
#include <cmath>
#include <stdexcept>

// Constructeur avec vérification d'arbitrage
CRRPricer :: CRRPricer(option* option, int depth, double asset_price, double up, double down, double interest_rate)
    : _option(option), _depth(depth), _asset_price(asset_price), _up(up), _down(down), _interest_rate(interest_rate), _tree(), _exercise_policy() {
    
    // Vérification si l'option est une option asiatique
    if (option->isAsianOption()) {
        throw std::invalid_argument("CRRPricer ne supporte pas les options asiatiques.");
    }
    
    if (!(down < interest_rate && interest_rate < up)) {
        throw std::invalid_argument("Arbitrage detecté: faites en sorte que down < interest_rate < up");
    }
    _tree.setDepth(_depth); // Initialiser la profondeur de l'arbre
    _exercise_policy.setDepth(_depth);
}

//Cette méthode construit un arbre binaire des valeurs de l'option en utilisant la méthode de Cox-Rox-Robinson
//Elle commentce par calculer la valeur du dernier niveau de l'arbre( à expiration) en appliquant le méthode payoff de l'option
//Ensuite elle remonte dans l'arbre en utilisant la formule donné dans l'énoncé
void CRRPricer::compute() {

    // Initialisation des valeurs au niveau d'expiration N
    for (int i = 0; i <= _depth; ++i) {
        double final_price = _asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, _depth - i); //on utilise simplement la formule S(N,i)=S0*U^i*D^(N-i)
        _tree.setNode(_depth, i, _option->payoff(final_price));
       _exercise_policy.setNode(_depth, i, false); //  À expiration, on ne se pose pas la question de l'exercice anticipé
    }
    
    // Induction pour calculer les valeurs aux niveaux précédents
    double q = (_interest_rate - _down) / (_up - _down);
    for (int n = _depth - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) { //on remonte l'arbre en calculant la valeur de l'option à chaque noeud
           
            double value = (q * _tree.getNode(n + 1, i + 1) + (1 - q) * _tree.getNode(n + 1, i)) / (1 + _interest_rate);
           
            if (_option->isAmericanOption()) {
                double intrinsic_value = _option->payoff(_asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, n - i));
                _tree.setNode(n, i, std::max(value, intrinsic_value));
             
                // Déterminer la politique d'exercice pour les options américaines
                _exercise_policy.setNode(n, i, intrinsic_value >= value);
            }
            else {
                // Options européennes et digitales : continuer la valeur de continuation seulement
                _tree.setNode(n, i, value);
            }
        }
    }
    _tree.display();
}


// Cette méthode calcul et renvoie le prix de l'option 
//Si l'argument est true elle calcul le prix de l'option sans passer par l'abre sinon elle utilise la méthode compute
double CRRPricer::operator()(bool closed_form) {
    if (closed_form) {
        // Formule fermée pour les options européennes uniquement
        if (_option->isAmericanOption()) {
            throw std::invalid_argument("Formule fermée non disponible pour les options américaines.");
        }

        double q = (_interest_rate - _down) / (_up - _down);
        double price = 0.0;

        for (int i = 0; i <= _depth; ++i) {
            double prob = std::exp(std::lgamma(_depth + 1) - std::lgamma(i + 1) - std::lgamma(_depth - i + 1))
                * std::pow(q, i) * std::pow(1 - q, _depth - i);
            double final_price = _asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, _depth - i);
            price += prob * _option->payoff(final_price);
        }

        return price / std::pow(1 + _interest_rate, _depth);
    }
    else {
        // Utiliser la méthode CRR
        compute();
        return _tree.getNode(0, 0);
    }
}
