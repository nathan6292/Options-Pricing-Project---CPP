#include "CRRPricer.h"
#include <cmath>

// Constructeur avec v�rification d'arbitrage
CRRPricer :: CRRPricer(option* option, int depth, double asset_price, double up, double down, double interest_rate)
    : _option(option), _depth(depth), _asset_price(asset_price), _up(up), _down(down), _interest_rate(interest_rate), _tree() {
    if (!(down < interest_rate && interest_rate < up)) {
        throw std::invalid_argument("Arbitrage detect�: faites en sorte que down < interest_rate < up");
    }
    _tree.setDepth(_depth); // Initialiser la profondeur de l'arbre
}

//Cette m�thode construit un arbre binaire des valeurs de l'option en utilisant la m�thode de Cox-Rox-Robinson
//Elle commentce par calculer la valeur du dernier niveau de l'arbre( � expiration) en appliquant le m�thode payoff de l'option
//Ensuite elle remonte dans l'arbre en utilisant la formule donn� dans l'�nonc�

void CRRPricer::compute() {
    // Initialisation des valeurs au niveau d'expiration N
    for (int i = 0; i <= _depth; ++i) {
        double final_price = _asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, _depth - i); //on utilise simplement la formule S(N,i)=S0*U^i*D^(N-i)
        _tree.setNode(_depth, i, _option->payoff(final_price));
    }

    // Induction pour calculer les valeurs aux niveaux pr�c�dents
    double q = (_interest_rate - _down) / (_up - _down);
    for (int n = _depth - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) { //on remonte l'arbre en calculant la valeur de l'option � chaque noeud
            double value = (q * _tree.getNode(n + 1, i + 1) + (1 - q) * _tree.getNode(n + 1, i)) / (1 + _interest_rate);
            _tree.setNode(n, i, value);
        }
    }
}


// Cette m�thode calcul et renvoie le prix de l'option 
//Si l'argument est true elle calcul le prix de l'option sans passer par l'abre sinon elle utilise la m�thode compute
double CRRPricer::operator()(bool closed_form) {
    if (closed_form) {
        // Formule ferm�e pour le prix de l'option
        double q = (_interest_rate - _down) / (_up - _down);//probabilit� risque neutre 
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
        // Calcul via la m�thode CRR
        compute();
        return _tree.getNode(0, 0);
    }
}
