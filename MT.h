#pragma once
#include <random>
class MT
{
private:
	static std::mt19937 generator; // Instance unique de std::mt19937 et du générateur

    // Constructeur privé pour empêcher l'instanciation
    MT();
public:

    
    static MT& instance();  // Méthode statique pour obtenir l'instance unique de MT

    // Méthode pour générer un nombre uniforme entre 0 et 1
    static double rand_unif();

    // Méthode pour générer un nombre selon une distribution normale
    static double rand_norm();

    // Supprimer les constructeurs de copie et d'affectation
    MT(const MT&) = delete;
    MT& operator=(const MT&) = delete;
};

