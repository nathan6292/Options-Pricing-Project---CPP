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

	//Destructor
	~CRRPricer();

	//Declaration of the function compute that computes all the values of the tree
	void compute();

	//Declaration of the function get that returns the value of the tree at the given depth and node
	double get(int, int);

	//Declaration of the function operator that returns the value of the tree at the root (Price of the option)
	double operator()(bool closed_form = false);

	//Declaration of the function getExercise that returns the value of the tree_bool at the given depth and node
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