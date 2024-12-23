#pragma once
#include "Option.h"
#include "optionType.h"
#include <vector>

// Class for Asian options derived from Option
class AsianOption : public Option
{
	// Declaration of the private variable time_steps
private :
	std::vector<double> time_steps;

public :
	// Declaration of the constructor with the parameter time_steps
	AsianOption(std::vector<double>);

	//Destructor
	~AsianOption();

	// Declaration of the overriden function payoffPath that returns the payoff of the option
	double payoffPath(std::vector<double>&) const override;

	// Declaration of the overriden function isAsianOption that returns true
	bool isAsianOption() const override;

	// Declaration of the getter function getTimeSteps that returns the time steps
	std::vector<double> getTimeSteps() const;

	// Define BlackScholesMCPricer as a friend class to access the private variable time_steps

};

