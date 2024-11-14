#pragma once
#include "Option.h"
#include "optionType.h"
#include <vector>
class AsianOption : public Option
{
private :
	std::vector<double> time_steps;
protected:
	optionType _type; 
public :
	AsianOption(std::vector<double>);
	double payoffPath(std::vector<double>) const;
	bool isAsianOption() const override;
	friend class BlackScholesMCPricer; 
};

