#include "vanillaoptions.h"
#include<iostream>
using namespace std;
#include<vector>
#include "Date.h"
#include<map>
#include<string>
#include<cmath>
#include<random>
#include<chrono>
#include<ctime>
#include<cstdlib>
vanillaoptions::vanillaoptions(double S, double r, double k, double day, double year, double month ,double v)
{

  this->S = S;
  this->r = r;
  this->v=v;
  this->k=k;
  this->day_of_maturity=day;
  this->year_of_maturity=year;
  this->month_of_maturity=month;}

vanillaoptions::~vanillaoptions()
{
    //dtor
}



double vanillaoptions:: periodDiff()
{   double T;
    Date date_of_maturity (day_of_maturity,month_of_maturity ,year_of_maturity);
    T=date_of_maturity.period_diff(); // returns the maturity periode in days units
    return T;
}

void  vanillaoptions::setstrike (double K)
{
    k=K;
}
double vanillaoptions:: getstrike()
{
  return k;
}
void vanillaoptions::set_risk_free_rate(double r)
{
  this->r=r;
}
double vanillaoptions:: get_risk_free_rate()
{
return r;
}
 double vanillaoptions::getVolatiliy()
{
    return v;
}
 double vanillaoptions::get_spot_price()
{
    return S;
}//*************************************************//
//**************Class PUT**************************//

Put::Put (double S, double r, double k, double day, double year, double month ,double v): vanillaoptions(S,r,k,day,year,month,v){}
Put::~Put()
{ }
double Put::payoff(double x)

{
 return std::max (k-x,0.0);
}
/*const*/ double Put :: Averagesequence()
{
    double T=this->periodDiff();
    double drift = (r-0.5*v*v)*T;
    double diffusion =(v*sqrt(T));
     //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
     //std::mt19937 gen(graine); // M
    //default_random_engine generator;
    unsigned int seed = static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    static std::mt19937 generateur(seed);
    //std::default_random_engine generator (graine);
    //std::uniform_int_distribution<std::mt19937::result_type> dist;
    normal_distribution<double> distribution(0.0, 1.0); // Mean (0.0) et std (1.0)
    double Z = distribution(generateur);
    double S_T=S*exp(drift+diffusion*Z);
    return S_T;

}

//*************************************************//
//**************Class Call**************************//
Call::Call(double S, double r, double k, double day, double year, double month ,double v):vanillaoptions(S,r,k,day,year,month,v){}


Call::~Call(){}

/*const */double  Call:: Averagesequence()
{   double T=periodDiff();
    double drift = (r-0.5*v*v)*T;
    double diffusion =(v*sqrt(T));
    unsigned int seed = static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    //std::default_random_engine generator(seed);
    static std::mt19937 generateur(seed);
    //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::normal_distribution<double> distribution(0.0, 1.0); // Mean (0.0) et std (1.0)
    double Z = distribution(generateur);
    double S_T=S*exp(drift+diffusion*Z);
    return S_T;}

double Call::payoff( double x)
{return std::max (x-k,0.0);}

//*************************************************//
//**************Class AsianCall**************************//

AsianCall:: AsianCall (double S, double r, double k, double day, double year, double month ,double v,int n):vanillaoptions(S,r,k,day,year,month,v),step(n) {}
AsianCall:: ~AsianCall() {}

/*const*/ double AsianCall::Averagesequence()
{
    vector<double> prices(step);// create a vector to store the log-normal distributed prices
    double dt = periodDiff()/step; // time step size
    double drift = (r-0.5*v*v);
    double price = S;
    // random number generator
   // unsigned seed =std::chrono::system_clock::now().time_since_epoch().count();
    //default_random_engine generator (seed);
    // normal distribution with mean 0 and standard deviation 1
    unsigned int seed = static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    //std::default_random_engine generator(seed);
    static std::mt19937 generateur(seed);
    std::normal_distribution<double> distribution (0.0,1.0);
    for(int i=1; i<step+1; i++)
    {      price = S*exp(drift*i*dt + v*sqrt(i*dt)*distribution(generateur));
           prices[i-1] = price; }
    if (prices.empty())
    {
        return 0.0;
    }
    else
    {
        double sum = accumulate(prices.begin(), prices.end(),0.0);
        return (sum/prices.size());
    }

}

double AsianCall::payoff( double x)
{
    return std:: max(x-k,0.0);
}



//*************************************************//
//**************Class AsianPUT*********************//


