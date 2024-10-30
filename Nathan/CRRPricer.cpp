#include "CRRPricer.h"
#include "BinaryTree.h"
#include <stdexcept>

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate){

	if (interest_rate >= up || interest_rate <= down)
		throw std::invalid_argument("The model admits Arbitrage!");

	this->option = option;
	this->depth = depth;
	this->asset_price = asset_price;
	this->up = up;
	this->down = down;
	this->interest_rate = interest_rate;

	tree = BinaryTree<Option*>(depth);
	for (int i = 0; i < depth; i++) {
			tree.setNode((*option).getExpiry(),i,option);
	}
}
