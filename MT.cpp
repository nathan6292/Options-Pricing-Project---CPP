#include "MT.h"
#include <iostream>

/// <summary>
/// Constructor of the class MT
/// 
/// The constructor initializes the generator with a random seed and the uniform and normal distributions
/// </summary>
MT::MT() : generator(std::random_device{}()),
uniform_dist(0.0, 1.0),
normal_dist(0.0, 1.0) {
    std::cout << "MT instance created." << std::endl;
}

// Give access to the unique instance of the class MT
MT& MT::get_instance() {
    static MT instance;
    return instance;
}

/// <summary>
/// Returns a random number between 0 and 1 using the uniform distribution
/// </summary>
/// <returns>Random number between 0 and 1</returns>
double MT::rand_unif() {
	MT& instance = get_instance();
	return instance.uniform_dist(instance.generator);
}

/// <summary>
/// Returns a random number following a normal distribution 
/// </summary>
/// <returns>Random number following a normal distribution</returns>
double MT::rand_norm(){
	MT& instance = get_instance();
	return instance.normal_dist(instance.generator);
}
