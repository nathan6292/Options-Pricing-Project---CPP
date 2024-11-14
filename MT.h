#pragma once
#include <random>
class MT
{
private:
	static std::mt19937 generator; // Instance unique de std::mt19937 et du g�n�rateur

    // Constructeur priv� pour emp�cher l'instanciation
    MT();
public:

    
    static MT& instance();  // M�thode statique pour obtenir l'instance unique de MT

    // M�thode pour g�n�rer un nombre uniforme entre 0 et 1
    static double rand_unif();

    // M�thode pour g�n�rer un nombre selon une distribution normale
    static double rand_norm();

    // Supprimer les constructeurs de copie et d'affectation
    MT(const MT&) = delete;
    MT& operator=(const MT&) = delete;
};

