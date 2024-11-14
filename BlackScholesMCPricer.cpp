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
	return _paths.size(); 
}

void BlackScholesMCPricer::generate(int nb_paths) {

	if ((*_option).isAsianOption()) {
		AsianOption* option = dynamic_cast<AsianOption*>(_option);
		for (int i = 0; i < nb_paths; i++) {
			std::vector<double> path;
			path.push_back(_initial_price);
			for (int j = 1; j < (*option).time_steps.size(); j++) {
				path.push_back(path[j - 1] * std::exp((_interest_rate - (_volatility * _volatility) / 2) * ((*option).time_steps[j] - (*option).time_steps[j - 1]) + _volatility * std::sqrt((*option).time_steps[j] - (*option).time_steps[j - 1]) * MT::rand_norm()));
			}
			_paths.push_back(path);
		}
	}
	else {
			for (int i = 0; i < nb_paths; i++) {
				std::vector<double> path;
				path.push_back(_initial_price * std::exp((_interest_rate - (_volatility * _volatility) / 2) * ((*_option).getExpiry()) + _volatility * std::sqrt((*_option).getExpiry()) * MT::rand_norm()));
				_paths.push_back(path);
			}
	}
}

double BlackScholesMCPricer::operator()() {
	if ((*_option).isAsianOption()) {
		AsianOption* option = dynamic_cast<AsianOption*>(_option);
		double sum_payoff = 0;
		for (int i = 0; i < _paths.size(); i++) {
			sum_payoff += _option->payoffPath(_paths[i]);
		}
		sum_payoff = sum_payoff / _paths.size();
		return sum_payoff * std::exp(-_interest_rate * (*option).getExpiry());
	}
	else{
		double sum_payoff = 0;
		for (int i = 0; i < _paths.size(); i++) {
			sum_payoff += (*_option).payoff(_paths[i][0]);
		}
		sum_payoff = sum_payoff / _paths.size();
		return sum_payoff * std::exp(-_interest_rate * (*_option).getExpiry());
	}
}

std::vector<double> BlackScholesMCPricer::confidenceInterval() {
	double mean = 0;
	double variance = 0;
	for (int i = 0; i < _paths.size(); i++) {
		mean += _option->payoffPath(_paths[i]);
	}
	mean = mean / _paths.size();
	for (int i = 0; i < _paths.size(); i++) {
		variance += pow(_option->payoffPath(_paths[i]) - mean, 2);
	}
	variance = variance / (_paths.size() - 1);
	double std_dev = sqrt(variance);
	double half_width = 1.96 * std_dev / sqrt(_paths.size());
	std::vector<double> interval;
	interval.push_back(mean - half_width);
	interval.push_back(mean + half_width);
	std::cout << "The confidence interval is: [" << interval[0] << ", " << interval[1] << "]" << std::endl;
	return interval;
}