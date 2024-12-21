#pragma once
#include "Option.h"
#include "BinaryTree.h"
#include "BlackScholesPricer.h"
#include "AmericanOption.h"

//Declaration of the class CRRPricer
class CRRPricer
{
public:
	//Declaration of the constructor with the parameters option, depth, asset_price, up, down, interest_rate
	CRRPricer(Option*, int, double, double, double, double);

	//Declaration of the constructor with the parameters option, depth, asset_price, up, down, interest_rate
	CRRPricer(Option*, int, double, double, double);
	void compute();
	double get(int, int);
	double operator()(bool closed_form = false);
	bool getExercise(int, int);

private:
	//Declaration of the private variables option, depth, asset_price, up, down, interest_rate and tree
	Option* option;
	int depth;
	double asset_price;
	double up;
	double down;
	double interest_rate;
	BinaryTree<double> tree;
	BinaryTree<bool> tree_bool;
};