#include <iostream>
#include "CallOption.h"
#include "PutOption.h"
#include "BlackScholesPricer.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
#include "AsianCallOption.h"
#include "AsianPutOption.h"
#include "BinaryTree.h"
#include "CRRPricer.h"	
#include "BlackScholesMCPricer.h"
#include "AmericanCallOption.h"
#include "AmericanPutOption.h"

int main() {

	std::cout << "Price using BlackScholes (closed form):" << std::endl; 
	CallOption call(5, 101);
	BlackScholesPricer call_pricer(&call, 100, 0.01, 0.1);
	std::cout << "Price of the EuropeanVanillaCallOption: " << call_pricer() << std::endl;

	PutOption put(5, 101);
	BlackScholesPricer put_pricer(&put, 100, 0.01, 0.1);
	std::cout << "Price of the EuropeanVanillaPutOption: " << put_pricer() << std::endl;

	EuropeanDigitalCallOption call_digital(5, 101);
	BlackScholesPricer call_digital_pricer(&call_digital, 100, 0.01, 0.1);
	std::cout << "Price of the EuropeanDigitalCallOption: " << call_digital_pricer() << std::endl;

	EuropeanDigitalPutOption put_digital(5, 101);
	BlackScholesPricer put_digital_pricer(&put_digital, 100, 0.01, 0.1);
	std::cout << "Price of the EuropeanDigitalPutOption: " << put_digital_pricer() << std::endl << std::endl;

	std::cout << "Price using the CRR Method: " << std::endl; 
	std::cout << "Tree of the EuropeanVanillaCallOption: " << std::endl << std::endl; 
	CRRPricer call_crr(&call, 5, 100, 0.05, -0.045, 0.01);
	std::cout << "Price of the EuropeanVanillaCallOption: "<< call_crr() << std::endl;
	std::cout << "Price of the EuropeanVanillaCallOption (closed form): " << call_crr(true) << std::endl << std::endl;

	std::cout << "Tree of the EuropeanVanillaPutOption: " << std::endl << std::endl;
	CRRPricer put_crr(&put, 5, 100, 0.05, -0.045, 0.01);
	std::cout << "Price of the EuropeanVanillaPutOption: " << put_crr() << std::endl;
	std::cout << "Price of the EuropeanVanillaPutOption (closed form): " << put_crr(true) << std::endl << std::endl;

	std::cout << "Tree of the EuropeanDigitalCallOption: " << std::endl << std::endl;
	CRRPricer call_digital_crr(&call_digital, 5, 100, 0.05, -0.045, 0.01);
	std::cout << "Price of the EuropeanDigitalCallOption: " << call_digital_crr() << std::endl;
	std::cout << "Price of the EuropeanDigitalCallOption (closed form): " << call_digital_crr(true) << std::endl << std::endl;

	std::cout << "Tree of the EuropeanDigitalPutOption: " << std::endl << std::endl;
	CRRPricer put_digital_crr(&put_digital, 5, 100, 0.05, -0.045, 0.01);
	std::cout << "Price of the EuropeanDigitalPutOption: " << put_digital_crr() << std::endl;
	std::cout << "Price of the EuropeanDigitalPutOption (closed form): " << put_digital_crr(true) << std::endl << std::endl;

    std::vector<double> path;
    // Remplir le vecteur avec les valeurs de 1 à 50
    for (double i = 0; i < 5; i=i+0.1) {
        path.push_back(i);
    }
    std::cout << path.size();
	AsianCallOption asian_call(path, 101);
	AsianPutOption asian_put(path, 101);
	
	std::cout << "Price using MC BlackScholes: " << std::endl; 

	BlackScholesMCPricer mc_call(&call, 100, 0.01, 0.1);
    std::vector<double> cint;
    //do {
      //  mc_call.generate(1000);
        //cint= mc_call.confidenceInterval();
    //} while (cint[1] - cint[0] > 1e-2);
    //Reset cint to 0 ,1
	//cint = { 0, 1 };
	mc_call.generate(10000000);
	std::cout << "Price of the EuropeanVanillaCallOption: " << mc_call() << std::endl; 

	BlackScholesMCPricer mc_put(&put, 100, 0.01, 0.1);
    do {
        mc_put.generate(1000);
        cint = mc_put.confidenceInterval();
    } while (cint[1] - cint[0] > 1e-2);
    std::cout << "Price of the EuropeanVanillaPutOption: " << mc_put() << std::endl;
    //Reset cint to 0 ,1
    cint = { 0, 1 };

	BlackScholesMCPricer mc_call_digital(&call_digital, 100, 0.01, 0.1);
    do {
        mc_call_digital.generate(1000);
        cint = mc_call_digital.confidenceInterval();
    } while (cint[1] - cint[0] > 1e-2);
    std::cout << "Price of the EuropeanDigitalCallOption: " << mc_call_digital() << std::endl;

    //Reset cint to 0 ,1
    cint = { 0, 1 };

	BlackScholesMCPricer mc_put_digital(&put_digital, 100, 0.01, 0.1);
    do {
        mc_put_digital.generate(1000);
        cint = mc_put_digital.confidenceInterval();
    } while (cint[1] - cint[0] > 1e-2);
    std::cout << "Price of the EuropeanDigitalPutOption: " << mc_put_digital() << std::endl;

    //Reset cint to 0 ,1
    cint = { 0, 1 };

	BlackScholesMCPricer mc_asian_call(&asian_call, 100, 0.01, 0.1);;
        mc_asian_call.generate(1000000);
        cint = mc_asian_call.confidenceInterval();
    std::cout << "Price of the AsianCallOption: " << mc_asian_call() << std::endl;
	std::cout << "Confidence interval: [" << cint[0] << ", " << cint[1] << "]" << std::endl;
    //Reset cint to 0 ,1
    cint = { 0, 1 };

	BlackScholesMCPricer mc_asian_put(&asian_put, 100, 0.01, 0.1);
        mc_asian_put.generate(1000000);
        cint = mc_asian_put.confidenceInterval();

    std::cout << "Price of the AsianPutOption: " << mc_asian_put() << std::endl;
    std::cout << "Confidence interval: [" << cint[0] << ", " << cint[1] << "]" << std::endl;
    //Reset cint to 0 ,1
    cint = { 0, 1 };

	std::cout << "Pice of AmericanOption using CRR: " << std::endl << std::endl;
	AmericanCallOption american_call(5, 101);
	CRRPricer american_call_crr(&american_call, 5, 100, 0.05, -0.045, 0.01);
	std::cout << "Price of the AmericanCallOption: " << american_call_crr() << std::endl;

	AmericanPutOption american_put(5, 101);
	CRRPricer american_put_crr(&american_put, 5, 100, 0.05, -0.045, 0.01);
	std::cout << "Price of the AmericanPutOption: " << american_put_crr() << std::endl;

    std::cout << std::endl << "*********************************************************" << std::endl;
    std::cout << std::endl << "Test 1" << std::endl;

    {

        double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
        CallOption opt1(T, K);
        PutOption opt2(T, K);


        std::cout << "European options 1" << std::endl << std::endl;

        {
            BlackScholesPricer pricer1(&opt1, S0, r, sigma);
            std::cout << "BlackScholesPricer price=" << pricer1() << ", delta=" << pricer1.delta() << std::endl;

            BlackScholesPricer pricer2(&opt2, S0, r, sigma);
            std::cout << "BlackScholesPricer price=" << pricer2() << ", delta=" << pricer2.delta() << std::endl;
            std::cout << std::endl;

            int N(150);
            double U = exp(sigma * sqrt(T / N)) - 1.0;
            double D = exp(-sigma * sqrt(T / N)) - 1.0;
            double R = exp(r * T / N) - 1.0;

            CRRPricer crr_pricer1(&opt1, N, S0, U, D, R);
            std::cout << "Calling CRR pricer with depth=" << N << std::endl;
            std::cout << std::endl;
            std::cout << "CRR pricer computed price=" << crr_pricer1() << std::endl;
            std::cout << "CRR pricer explicit formula price=" << crr_pricer1(true) << std::endl;
            std::cout << std::endl;

            CRRPricer crr_pricer2(&opt2, N, S0, U, D, R);
            std::cout << "Calling CRR pricer with depth=" << N << std::endl;
            std::cout << std::endl;
            std::cout << "CRR pricer computed price=" << crr_pricer2() << std::endl;
            std::cout << "CRR pricer explicit formula price=" << crr_pricer2(true) << std::endl;
        }
        std::cout << std::endl << "*********************************************************" << std::endl;
    }

    {
        std::cout << "Binary Tree" << std::endl << std::endl;
        BinaryTree<bool> t1;
        t1.setDepth(3);
        t1.setNode(1, 1, true);
        t1.display();
        t1.setDepth(5);
        t1.display();
        t1.setDepth(3);
        t1.display();


        BinaryTree<double> t2;
        t2.setDepth(2);
        t2.setNode(2, 1, 100);
        t2.display();
        t2.setDepth(4);
        t2.display();
        t2.setDepth(3);
        t2.display();

        BinaryTree<int> t3;
        t3.setDepth(4);
        t3.setNode(3, 0, 8);
        t3.display();
        t3.setDepth(2);
        t3.display();
        t3.setDepth(4);
        t3.display();

        std::cout << std::endl << "*********************************************************" << std::endl;
    }

    {

        double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
        EuropeanDigitalCallOption opt1(T, K);
        EuropeanDigitalPutOption opt2(T, K);


        std::cout << "European options 2" << std::endl << std::endl;

        {
            BlackScholesPricer pricer1(&opt1, S0, r, sigma);
            std::cout << "BlackScholesPricer price=" << pricer1() << ", delta=" << std::setprecision(4)<< pricer1.delta() << std::endl;

            BlackScholesPricer pricer2(&opt2, S0, r, sigma);
            std::cout << "BlackScholesPricer price=" << pricer2() << ", delta=" << std::setprecision(4) << pricer2.delta() << std::endl;
            std::cout << std::endl;

            int N(150);
            double U = exp(sigma * sqrt(T / N)) - 1.0;
            double D = exp(-sigma * sqrt(T / N)) - 1.0;
            double R = exp(r * T / N) - 1.0;

            CRRPricer crr_pricer1(&opt1, N, S0, U, D, R);
            std::cout << "Calling CRR pricer with depth=" << N << std::endl;
            std::cout << std::endl;
            std::cout << "CRR pricer computed price=" << crr_pricer1() << std::endl;
            std::cout << "CRR pricer explicit formula price=" << crr_pricer1(true) << std::endl;
            std::cout << std::endl;

            CRRPricer crr_pricer2(&opt2, N, S0, U, D, R);
            std::cout << "Calling CRR pricer with depth=" << N << std::endl;
            std::cout << std::endl;
            std::cout << "CRR pricer computed price=" << crr_pricer2() << std::endl;
            std::cout << "CRR pricer explicit formula price=" << crr_pricer2(true) << std::endl;
        }
        std::cout << std::endl << "*********************************************************" << std::endl;
    }

    std::cout << std::endl << "Test 2" << std::endl;

    double S0(100), K(101), T(5), r(0.01), sigma(0.1);
    std::vector<Option*> opt_ptrs;
    opt_ptrs.push_back(new CallOption(T, K));
    opt_ptrs.push_back(new PutOption(T, K));
    opt_ptrs.push_back(new EuropeanDigitalCallOption(T, K));
    opt_ptrs.push_back(new EuropeanDigitalPutOption(T, K));

    std::vector<double> fixing_dates;
    for (int i = 1; i <= 50; i++) {
        fixing_dates.push_back(0.1 * i);
    }
    opt_ptrs.push_back(new AsianCallOption(fixing_dates, K));
    opt_ptrs.push_back(new AsianPutOption(fixing_dates, K));


    std::vector<double> ci;
    BlackScholesMCPricer* pricer;

   for (auto& opt_ptr : opt_ptrs) {
        pricer = new BlackScholesMCPricer(opt_ptr, S0, r, sigma);
        do {
            pricer->generate(10000);
            ci = pricer->confidenceInterval();
        } while (ci[1] - ci[0] > 1e-2);
        std::cout << "nb samples: " << pricer->getNbPaths() << std::endl;
        std::cout << "price: " << (*pricer)() << std::endl;
        std::cout << "confidence interval: [" << ci[0] << ", " << ci[1] << "]" << std::endl << std::endl;
        delete pricer;
        delete opt_ptr;
    }

    std::cout << std::endl << "*********************************************************" << std::endl;
    std::vector<Option*> opt3_ptrs;
    opt3_ptrs.push_back(new CallOption(T, K));
    opt3_ptrs.push_back(new PutOption(T, K));
    opt3_ptrs.push_back(new EuropeanDigitalCallOption(T, K));
    opt3_ptrs.push_back(new EuropeanDigitalPutOption(T, K));
    opt3_ptrs.push_back(new AmericanCallOption(T, K));
    opt3_ptrs.push_back(new AmericanPutOption(T, K));

    CRRPricer* pricercrr;

    for (auto& opt3_ptr : opt3_ptrs) {
        pricercrr = new CRRPricer(opt3_ptr, 150, S0, r, sigma);

        pricercrr->compute();

        std::cout << "price: " << (*pricercrr)() << std::endl << std::endl;
        delete pricercrr;
        delete opt3_ptr;

    }

}
