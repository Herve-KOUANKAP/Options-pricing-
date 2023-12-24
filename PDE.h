#ifndef PDE_H
#define PDE_H
#include"vanillaoptions.h"

class PDE {
 public:
  // PDE Coefficients
  PDE(vanillaoptions& options);

  virtual ~PDE();

  double diff_coeff(double t, double x) const;
  double conv_coeff(double t, double x) const;
  double zero_coeff(double t, double x) const;
  double source_coeff(double t, double x) const;

  double boundary_left(double t, double x) const;
  double boundary_right(double t, double x) const;
  double init_cond(double x) const;
  vanillaoptions* option;
};

#endif // PDE_H
