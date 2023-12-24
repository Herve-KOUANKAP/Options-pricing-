#include <fstream>
#include<iostream>
using namespace std;
// to output the solution surface to disk
#include "FDM.h"
#include"PDE.h"
#include"math.h"
#include<cmath>
#include<map>
#include "Date.h"
#include "vanillaoptions.h"
#include<vector>

// a constructor for the abstract base class FDMBase
FDMBase::FDMBase(double _x_dom, int  _J,
                 double _t_dom, int _N,
                PDE* _pde)
  : x_dom(_x_dom), J(_J), t_dom(_t_dom), N(_N), pde(_pde) {}

FDMEulerExplicit::FDMEulerExplicit(double _x_dom, int _J,
                                   double _t_dom, int _N,
                                   PDE* _pde)
  : FDMBase(_x_dom, _J, _t_dom, _N, _pde) {
  calculate_step_sizes();
  set_initial_conditions();
}

void FDMEulerExplicit::calculate_step_sizes() {
  dx = x_dom/static_cast<double>(J-1);
  dt = t_dom/(N-1);
}

void FDMEulerExplicit::set_initial_conditions() {
  // Spatial settings
  double cur_spot = 0.0;

  old_result.resize(J, 0.0);
  new_result.resize(J, 0.0);
  x_values.resize(J, 0.0);

  for (int  j=0; j<J; j++) {
    cur_spot = static_cast<double>(j)*dx;
    old_result[j] = pde->init_cond(cur_spot);
    x_values[j] = cur_spot;
  }

  // Temporal settings
  prev_t = 0.0;
  cur_t = 0.0;
}

void FDMEulerExplicit::calculate_boundary_conditions() {
  new_result[0] = pde->boundary_left(prev_t, x_values[0]);
  new_result[J-1] = pde->boundary_right(prev_t, x_values[J-1]);
    //new_result[J-1] = pde->boundary_left(prev_t, x_values[J-1]);
    //new_result[0] = pde->boundary_right(prev_t, x_values[0]); //PUT BOUNDARIES;

}

void FDMEulerExplicit::calculate_inner_domain() {
  // Only use inner result indices (1 to J-2)
  for (int  j=1; j<J-1; j++) {
    // Temporary variables used throughout
    double dt_sig = dt * (pde->diff_coeff(prev_t, x_values[j]));
    double dt_sig_2 = dt * dx * 0.5 * (pde->conv_coeff(prev_t, x_values[j]));

    // Differencing coefficients (see \alpha, \beta and \gamma in text)
    alpha = dt_sig - dt_sig_2;
    beta = dx * dx - (2.0 * dt_sig) + (dt * dx * dx * (pde->zero_coeff(prev_t, x_values[j])));
    gamma = dt_sig + dt_sig_2;

    // Update inner values of spatial discretisation grid (Explicit Euler)
    new_result[j] = ( (alpha * old_result[j-1]) +
                      (beta * old_result[j]) +
                      (gamma * old_result[j+1]) )/(dx*dx) -
      (dt*(pde->source_coeff(prev_t, x_values[j])));
  }
}
void FDMEulerExplicit::step_march() {
  std::ofstream fdm_out("fdm_put_yes.csv");
  std::ofstream theorique ("theorique.csv");


  double epsilon=0;

  while(cur_t < t_dom) {
    cur_t = prev_t + dt;
    calculate_boundary_conditions();
    calculate_inner_domain();
    for (int j=0; j<J; j++) {
      //fdm_out << x_values[j] << " " << prev_t << " " << new_result[j] << std::endl;
      if (prev_t==t_dom)
      {
         theorique<<x_values[j]-pde->option->getstrike()<<endl;
      }
      else
      {
      double d1=log(x_values[j] /(pde->option->getstrike()))+(pde->option->get_risk_free_rate()+0.5*pow(pde->option->getVolatiliy(),2))*(t_dom-prev_t)/(pde->option->getVolatiliy()*sqrt(t_dom-prev_t));
      double d2=d1-pde->option->getVolatiliy()*sqrt(t_dom-prev_t);
      theorique<<x_values[j]* 0.5 * (1 + std::erf((d1) / std::sqrt(2.0)))-pde->option->getstrike()*exp(-pde->option->get_risk_free_rate()*(t_dom-prev_t))*(1 + std::erf((d2) / std::sqrt(2.0)))<<endl;
      }

    }

    old_result = new_result;
    prev_t = cur_t;
  }

  //fdm_out.close();
    theorique.close();
}
