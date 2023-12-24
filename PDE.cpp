#include "PDE.h"
#include <iostream>
using namespace std;
#include "Binomialmodel.h"
#include<cmath>
#include<map>
#include "Date.h"
#include "vanillaoptions.h"
PDE::PDE(vanillaoptions& options)
{
    option=&options;
}

PDE::~PDE()
{
    //dtor
}
// Diffusion coefficient
double PDE::diff_coeff(double t, double x) const {
  double vol = option->getVolatiliy();
  return 0.5*vol*vol*x*x;  // \frac{1}{2} \sigma^2 S^2
}

// Convection coefficient
double PDE::conv_coeff(double t, double x) const {
  return (option->get_risk_free_rate())*x;  // rS
}

// Zero-term coefficient
double PDE::zero_coeff(double t, double x) const {
  return -(option->get_risk_free_rate());  // -r
}

// Source coefficient
double PDE::source_coeff(double t, double x) const {
  return 0.0;
}

// Left boundary-condition (vanilla call option)
double PDE::boundary_left(double t, double x) const {
  return 0.0;  // Specifically for a CALL option
}

// Right boundary-condition (vanilla call option)
double PDE::boundary_right(double t, double x) const {
  // This is via Put-Call Parity and works for a call option
  //(x-(option->getstrike())*exp(-(option->get_risk_free_rate())*((option->periodDiff())-t))); //for call
  return
  (option->getstrike()*exp(-(option->get_risk_free_rate())*((option->periodDiff())-t))-x);
}
double PDE::init_cond(double x) const {
  return (option->payoff(x));
}
