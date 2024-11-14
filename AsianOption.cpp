#include "AsianOption.h"
#include <stdexcept>

AsianOption::AsianOption(std::vector<double> times) : Option(times[times.size() - 1]) {
	if (times[times.size()-1] < 0)
		throw std::invalid_argument("Expiry must be positive");


	time_steps = times; 
}

double AsianOption::payoffPath(std::vector<double> spots) const{
	double mean_spots = 0; 

	for (int i = 0; i < spots.size(); i++) {
		mean_spots += spots[i];
	}
	mean_spots = mean_spots / spots.size(); 

	return payoff(mean_spots);
}


bool AsianOption::isAsianOption() const{
	return true; 
}
