#include "CRRPricer.h"
#include "BinaryTree.h"
#include <stdexcept>
#include <cmath>

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate){

	if (1+ interest_rate >= up || 1+ interest_rate <= down)
		throw std::invalid_argument("The model admits Arbitrage!");

	this->option = option;
	this->depth = depth;
	this->asset_price = asset_price;
	this->up = up;
	this->down = down;
	this->interest_rate = interest_rate;
    this->closed_form = false;

	tree = BinaryTree<Option*>(depth);
	for (int i = 0; i < depth; i++) {
			tree.setNode((*option).getExpiry(),i,option);
	}
}


int factorielle(int n)
{
    if((n==1)||(n==0))
    {
        return 1;
    }
    return n*factorielle(n-1);
}

void CRRPricer::compute(){
    double q = (interest_rate-down)/(up-down);
    double x;
    for(int i = 0;i<=depth;i++)
    {
        x = asset_price*std::pow(1+up,i)*std::pow(1+down,depth-i);
        tree.setNode(depth,i,x);
    }
    for(int n = depth - 1; n >= 0; n--)
    {
        for(int i = 0; i <= n; i++)
        {
            x = (q* payoff(tree.getNode(n+1,i+1))+((1-q)*payoff(tree.getNode(n+1,i))))/(1+interest_rate);
            tree.setNode(n,i,x);
        }
    }
    closed_form = true;
}

double CRRPricer::get(int n, int i){
     if (n > depth || i > n) {
        throw std::out_of_range("Invalid tree indices");
    }
    return payoff(tree.getNode(n,i));
}

double CRRPricer::operator()(){
    if (!closed_form)
    {
        return (*option).payoff(asset_price*pow(1+up,i)*pow(1+down,depth-i));
    }
    else
    {
        double q = (interest_rate-down)/(up-down);
        double x = 0;
        for(int j = 0; j<depth;j++)
        {
            x += ((factorielle(depth)/(factorielle(j)*factorielle(depth-j)))*(pow(q,j)*pow(1-q,depth-j)))*get(depth,j);
        }
        return x*pow(1/(1+interest_rate),depth);
    }
}
