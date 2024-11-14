#include "BlackScholesMCPricer.h"
#include <cmath>
#include <iostream>

BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility) {
	_option = option;
	_initial_price = initial_price; 
	_interest_rate = interest_rate;
	_volatility = volatility; 
	npaths = 0; 
}

int BlackScholesMCPricer::getNbPaths() {
	return npaths; 
}

void BlackScholesMCPricer::generate(int nb_paths) {

	if ((*_option).isAsianOption()) {
		AsianOption* option = dynamic_cast<AsianOption*>(_option);
		for (int i = 0; i < nb_paths; i++) {
			double sum_path = _initial_price;
			double last = _initial_price;
			for (int j = 1; j < (*option).time_steps.size(); j++) {
				double price = last * std::exp((_interest_rate - (_volatility * _volatility) / 2) * ((*option).time_steps[j] - (*option).time_steps[j - 1]) + _volatility * std::sqrt((*option).time_steps[j] - (*option).time_steps[j - 1]) * MT::rand_norm());
				sum_path += price;
				last = price;
			}
			sum_path = sum_path / (*option).time_steps.size();
			double pay = (*_option).payoff(sum_path);
			sum += pay;
			sum_squared += pay*pay;
			npaths++;
		}
	}
	else {
			for (int i = 0; i < nb_paths; i++) {
				double pay = (*_option).payoff(_initial_price * std::exp((_interest_rate - (_volatility * _volatility) / 2) * ((*_option).getExpiry()) + _volatility * std::sqrt((*_option).getExpiry()) * MT::rand_norm()));
				sum += pay;
				sum_squared += pay * pay;
				npaths++;
			}
	}
}

double BlackScholesMCPricer::operator()() {
		return sum/npaths * std::exp(-_interest_rate * (*_option).getExpiry());
}

std::vector<double> BlackScholesMCPricer::confidenceInterval() {
	double mean = 0;
	double variance = 0;
	mean += sum/npaths;
	double std_dev = sqrt((sum_squared/npaths)-mean*mean);
	double half_width = 1.96 * std_dev / sqrt(npaths);
	std::vector<double> interval;
	interval.push_back(mean - half_width);
	interval.push_back(mean + half_width);
	//std::cout << "The confidence interval is: [" << interval[0] << ", " << interval[1] << "]" << std::endl;
	return interval;
}