#include <iostream>
using namespace std;
#include "Binomialmodel.h"
#include<cmath>
#include<map>
#include "Date.h"
#include "vanillaoptions.h"

Binomialmodel::Binomialmodel( vanillaoptions & option,int n)
{
  option_ptr=&option;
  //option_ptr= new vanillaoptions (option->get_spot_price(), option->get_risk_free_rate(), option->getstrike(), option->getDayOfMaturity(), option->getYearOfMaturity(), option->getMonthOfMaturity() ,option->getVolatiliy());
  this->n_period=n;
  u =exp(option.getVolatiliy()*sqrt(option.periodDiff()/n));

}
 Binomialmodel:: Binomialmodel(int periods) : n_period(periods) {}


Binomialmodel::~Binomialmodel()
{

  //delete option_ptr;
    //dtor
}

double Binomialmodel::riskneutralprobability()   //discrete discounting
{

    return ((exp(option_ptr->get_risk_free_rate()*option_ptr->periodDiff()/n_period)-1/u))/(u-1/u);
}

double Binomialmodel:: pricer()
{
   //double** treematrix = new double*[n_period+1]; // pointers table on possible spot prices
   //double** payoffmatrix = new  double*[n_period+1]; // pointers table on option payoff in all tree nodes
    // pointers table on possible options prices in all tree nodes
   //cout<<"ffffffffff"<<option_ptr->get_spot_price()<<endl;

   /* for (int i = 0; i < n_period; ++i)
        {
        pricematrix[i]=new double[n_period];
        }*/

        //treematrix[i] = new double[n_period+1];
        //payoffmatrix[i]=new double[n_period+1];
        //cout<<"helloooooo"<<endl;

    /*for (int i=0;i<n_period+1;i++)
    {
        for (int j=0;j<n_period+1;j++)
        {
            if ( j<i)
            {
              treematrix[i][j]=0.0;
              payoffmatrix[i][j]=0.0;
              pricematrix[i][j]=0.0;
              //cout<<"helloooooo"<<endl;
            }
            else
            {
             treematrix[i][j]=option_ptr->get_spot_price()*pow(u,j-i)*pow(u,-i);
             payoffmatrix[i][j]=option_ptr->payoff(treematrix[i][j]);
             //cout<<"helloooooo"<<endl;

            }
    }
    }*/
    double** pricematrix = new double*[n_period+1];
    for (int i = 0; i < n_period+1; ++i)
        {pricematrix[i]=new double[n_period+1];}

     for (int i = 0; i < n_period+1; ++i)
    {pricematrix[i][n_period] =option_ptr->payoff(option_ptr->get_spot_price()*pow(u,n_period-i)*pow(u,-i));}

    double q=riskneutralprobability();
    double r=option_ptr->get_risk_free_rate();
     for (int i=n_period-1;i>-1;i--)
    {
        for (int j=n_period-1;j>-1;j--)
        {
               /*if (payoffmatrix[i][j]==0.0)
                {pricematrix[i][j]=0.0;
                //cout<<pricematrix[i][j]<<endl;
                //cout<<"hellobombbooom"<<endl;
                e*///pricematrix[i][j]=max(payoffmatrix[i][j],(q*pricematrix[i][j+1]+(1-q)*pricematrix[i+1][j+1])*exp(-r*option_ptr->periodDiff()/n_period));
            if (j>=i)
                pricematrix[i][j]=max(option_ptr->payoff(option_ptr->get_spot_price()*pow(u,j-i)*pow(u,-i)),(q*pricematrix[i][j+1]+(1-q)*pricematrix[i+1][j+1])*exp(-r*option_ptr->periodDiff()/n_period));}}
        double   price=pricematrix[0][0];



        delete pricematrix;

     return (price );    // it returns the American Option price at the first node with backward pricing
}
