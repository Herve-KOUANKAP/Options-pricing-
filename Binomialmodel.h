#ifndef BINOMIALMODEL_H
#define BINOMIALMODEL_H

#include <iostream>
using namespace std ;
#include "vanillaoptions.h"
#include<vector>
#include <map>
#include "Date.h"


class Binomialmodel
{
    public:
        Binomialmodel(int );
        Binomialmodel( vanillaoptions &option,int n);

        virtual ~Binomialmodel();
        double riskneutralprobability(); // generate a recombinant tree : ud=1
        double pricer() ;


    protected:

    private:
       /* double spotprice ;
        double r;  //risk free interest rate
        double u ;// up and down is 1/u

        double strikeprice;
        char type;
        double Maturity;*/
        vanillaoptions* option_ptr;
        int n_period;
        double u;


};

#endif // BINOMIALMODEL_H
