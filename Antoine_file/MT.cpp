#include "MT.h"

// D�claration de l'instance unique de std::mt19937 dans MT.cpp
std::mt19937 MT::generator;

// Constructeur priv�
MT::MT() {
    std::random_device rd;
    generator.seed(rd());  // Initialisation avec un seed unique
}

// M�thode statique pour obtenir l'instance unique de MT
MT& MT::instance() {
    static MT instance;  // Initialisation unique
    return instance;
}

// M�thode pour g�n�rer un nombre uniforme entre 0 et 1
double MT::rand_unif() {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(generator);
}

// M�thode pour g�n�rer un nombre selon une distribution normale
double MT::rand_norm() {
    std::normal_distribution<double> dist(0.0, 1.0);
    return dist(generator);
}
