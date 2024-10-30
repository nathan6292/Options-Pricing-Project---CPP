#include <iostream>
#include "CallOption.h"
#include "PutOption.h"
#include "BlackScholesPricer.h"
#include "BinaryTree.h"

int main() {
	std::cout << "Hello, World!" << std::endl;

	CallOption call(5, 101);
	BlackScholesPricer call_pricer(&call, 100, 0.01, 0.1);
	std::cout << "Price of the option: " << call_pricer() << std::endl;

	
}