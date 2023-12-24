#ifndef VANILLAOPTIONS_H
#define VANILLAOPTIONS_H
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include<string>
#include "Date.h"

class vanillaoptions
{
    public:
        vanillaoptions(double S, double r, double k, double day, double year, double month ,double v);
        virtual ~vanillaoptions();
        double periodDiff();
        virtual  double payoff ( double  x) =0; //const
        virtual double  Averagesequence() =0; //const
        double getstrike() ;
        void setstrike(double);
        void setV(double);
        double get_spot_price();
        double getVolatiliy();
        //double getV();

        //void setS(double);
        //double getS();

        void set_risk_free_rate(double);
        double get_risk_free_rate();

        void setYearOfMaturity(double);
        double getYearOfMaturity();

        void setMonthOfMaturity(double);
        double getMonthOfMaturity();

        void setDayOfMaturity(double);
        double getDayOfMaturity();

    protected:
        double k, v, S , r, day_of_maturity, month_of_maturity, year_of_maturity;
         //int M; pour le moment pas besoin

    private:
};
class Put : public vanillaoptions
{
  public :
      Put(double S, double r, double k, double day, double year, double month ,double v); // constructor


      virtual ~Put();//  destructor
      /*const */double payoff( double x) override;//const
      /*const*/ double Averagesequence() override ;

};
class Call : public vanillaoptions{


  public :
      Call(double S, double r, double k, double day, double year, double month ,double v); // constructor


      virtual ~Call();//  destructor
      double payoff( double x)  override;
      double  Averagesequence() override ;




};
class AsianCall : public vanillaoptions{

    private :
        int step ; // on récupère le prix de l'option sur n fois
    public :
        AsianCall (double S, double r, double k, double day, double year, double month ,double v,int n);
        virtual ~AsianCall() ;
        double Averagesequence( ) override ;
        double payoff( double x)  override ;




};
// reste à coder le AsianPUT

#endif // VANILLAOPTIONS_H
