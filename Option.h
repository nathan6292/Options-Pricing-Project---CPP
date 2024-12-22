#pragma once
#include <vector>

//Declaration of the class Option
class Option
{
//Declaration of the private variable expiry
private: 
	double _expiry;

public:
	//Declaration of the functions
	double getExpiry() const;
	
	/*Declaration of the pure virtual function payoff, pure virtual functions are function
	that are declared in the base class but not defined, they are defined in the derived classes*/
	virtual double payoff(double) const = 0;

	//Declaration of the function payoffPath for Asian options
	virtual double payoffPath(std::vector<double>&) const; 

	//Declaration of the constructor with the parameter expiry
	Option(double);

	//Declaration of the virtual function isAsianOption, this function is used to check if the option is an Asian option
	virtual bool isAsianOption() const; 
	//Declaration of the function isAmericanOption, this function is used to check if the option is an American option
	virtual bool isAmericanOption() const;
};

