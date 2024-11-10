#include"Option.h"
#include<iostream>
using namespace std;

Option::Option(double expiry) : _expiry(expiry) {}

double Option::getExpiry()const
{
	return _expiry;
}
