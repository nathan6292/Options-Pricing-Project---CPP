#include <random>

class MT {
private:
    static std::mt19937* instance;  
    MT();

public:
    static std::mt19937* getInstance();
    static double rand_unif();
    static double rand_norm();
};

