#pragma once
#include<iostream>
#include"EuropeanVanillaOption.h"

class PutOption : public EuropeanVanillaOption
{
public:
	PutOption(double, double);
	optionType GetOptionType()const override;
};
