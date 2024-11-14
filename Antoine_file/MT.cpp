#include "MT.h"

// Déclaration de l'instance unique de std::mt19937 dans MT.cpp
std::mt19937 MT::generator;

// Constructeur privé
MT::MT() {
    std::random_device rd;
    generator.seed(rd());  // Initialisation avec un seed unique
}

// Méthode statique pour obtenir l'instance unique de MT
MT& MT::instance() {
    static MT instance;  // Initialisation unique
    return instance;
}

// Méthode pour générer un nombre uniforme entre 0 et 1
double MT::rand_unif() {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(generator);
}

// Méthode pour générer un nombre selon une distribution normale
double MT::rand_norm() {
    std::normal_distribution<double> dist(0.0, 1.0);
    return dist(generator);
}
