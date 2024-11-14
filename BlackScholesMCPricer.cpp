#include "BlackScholesMCPricer.h"

//Cette methode genere nb_paths chemins possible du prix du sous-jacent à l'échéance de l'option
void BlackScholesMCPricer::generate(int nb_paths) {
    double sum_payoffs = 0.0;

    for (int i = 0; i < nb_paths; ++i) {
        // Generate a random standard normal variable
        double Z = MT::rand_norm();
        double expi = _option->getExpiry();
        // Simulate end-of-period asset price for European option (m = 1)
        double S_T = _initial_price * std::exp((_interest_rate - 0.5 * _volatility * _volatility) * expi + _volatility * Z* std::sqrt(expi));

        //On trouve le payoff avec le prix trouvé plus haut et on actualise pour obtenir sa valeur actuelle en multipliant par e^-r
        double payoff = _option->payoff(S_T);
        double discounted_payoff = payoff * std::exp(-_interest_rate*expi);

        // Update running sums for the estimate and variance calculation
        sum_payoffs += discounted_payoff;
        _sum_squared += discounted_payoff * discounted_payoff;
    }

    // Update the price estimate
    _nb_paths += nb_paths;//pourquoi pas faire _nb_paths++ ?
    _price_estimate = sum_payoffs / _nb_paths; //moyenne de tout les payoff généré par les différents chemins
}

double BlackScholesMCPricer::operator()() const { // retourne l'estimation du prix de l'option 
    if (_nb_paths == 0) {
        throw std::runtime_error("Price estimate undefined: no paths generated yet.");
    }
    return _price_estimate;
}

std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
    if (_nb_paths == 0) {
        throw std::runtime_error("Impossible de determiner un intervalle de confiance car aucun chemin n'a été généré.");
    }

    double variance = (_sum_squared / _nb_paths) - (_price_estimate * _price_estimate);
    double standard_error = std::sqrt(variance / _nb_paths);
    double margin = 1.96 * standard_error; // Pour avoir 95% de confiance

    return { _price_estimate - margin, _price_estimate + margin };
}
