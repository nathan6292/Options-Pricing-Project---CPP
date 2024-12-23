#pragma once
#include <random>

// Declaration of the class MT
class MT {
public:
	//Declaration of the function rand_unif that returns a random number between 0 and 1
    static double rand_unif();

	//Declaration of the function rand_norm that returns a random number following a normal distribution
    static double rand_norm();

private:
	//Declaration of the constructor of the class MT in private in order to make it a singleton
    MT();

	//Declaration of the copy constructor and the operator= in private in order to make it a singleton
    MT(const MT&) = delete;
    MT& operator=(const MT&) = delete;

	//Declaration of the static function get_instance that returns the instance of the class MT
    static MT& get_instance();

	//Declaration of the private variables generator, uniform_dist and normal_dist
    std::mt19937 generator;                     
    static std::uniform_real_distribution<double> uniform_dist; 
    static std::normal_distribution<double> normal_dist;
};
