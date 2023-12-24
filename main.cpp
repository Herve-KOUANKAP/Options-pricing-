#include <iostream>
#include "vanillaoptions.h"
#include "MonteCarlo.h"
#include <tuple>
#include "Binomialmodel.h"
#include"PDE.h"
#include"FDM.h"
using namespace std;

int main()
{
    double S,r,v,K,day,month,year;
    //unsigned long int M=1000;
    /*cout<<"Spot price :"<<endl;
    cin>>S;
    //euro.S=100;
    cout<<"STRIKE price :"<<endl;
    cin>>K;
    //euro.K=110;
    cout<<"Risk interest :"<<endl;
    cin>>r;
    //euro.r=0.05;
    cout<<"dayMaturity :"<<endl;
    cin>>day;
    cout<<"yearMaturity :"<<endl;
    cin>>year;
    cout<<"monthMaturity :"<<endl;
    cin>>month;
    //euro.T=1.0;
    cout<<"Volatility :"<<endl;
    cin>>v;
    //euro.v=0.2;*/
    //Put *P;
    //Call * C;
    /*P=new Put(S=100,r=0.05,K=110,day=13,year=2024,month=12,v=0.2);
    C=new Call (S=10,r=0.05,K=12,day=20,year=2024,month=9,v=0.2);
    Call CA =Call(S=100,r=0.05,K=110,day=17,year=2024,month=12,v=0.25);
    Put PA=Put(S=10,r=0.05,K=12,day=20,year=2024,month=9,v=0.3);

    AsianCall* AS=new AsianCall(S=100,r=0.05,K=110,day=19,year=2024,month=12,v=0.2,10);

    //AsianPut* AS=new AsianPut(S=100,r=0.05,K=110,day=13,year=2024,month=12,v=0.2,10);// not yet implemented

    MonteCarlo* Q;
    Q=new MonteCarlo(M);
    int n=3;
    cout<<"the EUROPEEN CALL OPTION PRICE IS "<<get<0>(Q->pricer(C))<<endl;
    cout<<"the EUROPEEN CALL OPTION std deviation IS "<<get<1>(Q->pricer(C))<<endl;

    cout<<"the EUROPEEN PUT OPTION PRICE IS "<<get<0>(Q->pricer(P))<<endl;
    cout<<"the EUROPEEN PUT OPTION std deviation IS "<<get<1>(Q->pricer(P))<<endl;
       cout<<"the EUROPEEN Asian Call OPTION PRICE IS "<<get<0>(Q->pricer(AS))<<endl;
    cout<<"the EUROPEEN Asian Call OPTION std deviation IS "<<get<1>(Q->pricer(AS))<<endl;
    Binomialmodel*G=new Binomialmodel(CA,n);
    cout <<"#############################################"<<endl;
    cout<<"the EUROPEEN  Call OPTION price with n="<<n<<" IS "<<G->pricer()<<endl;
    cout<<"**************************************************"<<endl;*/
    // FDM discretisation parameters
  double x_dom = 100.0;       // Spot goes from [0.0, 1.0]
  int J = 20;
  int N = 20;

  // Create the PayOff and Option objects
  //VanillaOption* call_option = new VanillaOption(K, r, T, v, pay_off_call);
  //C=new Call (S=10,r=0.05,K=12,day=20,year=2024,month=9,v=0.2);
  Call C =Call(S=1,r=0.05,K=70,day=20,year=2024,month=12,v=0.2);
  Put P =Put(S=1,r=0.05,K=0.5,day=20,year=2024,month=12,v=0.2);
  double t_dom =1.0;
  cout<<t_dom;        // Time period as for the option

  // Create the PDE and FDM objects
   PDE* bs_pde = new PDE(C);
  FDMEulerExplicit fdm_euler(x_dom, J, t_dom, N, bs_pde);

  // Run the FDM solver
  fdm_euler.step_march();

  // Delete the PDE, PayOff and Option objects
  delete bs_pde;
  //delete fdm_euler;
//  delete C;

    return 0;
}
