#include "MT.h"
#include <iostream>
std::mt19937* MT::instance = nullptr;

MT::MT() {}  

std::mt19937* MT::getInstance() {
    if (!instance) {
        instance = new std::mt19937(std::random_device{}());  
        std::cout << "Instance of MT generated" << std::endl;
    }
    return instance;
}

double MT::rand_unif() {
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    return dis(*getInstance());
}

double MT::rand_norm() {
    std::normal_distribution<double> dis(0.0, 1.0); 
    return dis(*getInstance());  
}
