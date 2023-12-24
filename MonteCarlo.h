#ifndef MONTECARLO_H
#define MONTECARLO_H
#include <iostream>
#include <tuple>
#include "vanillaoptions.h"


class MonteCarlo
{
    public:

        MonteCarlo(unsigned long int M);
        virtual ~MonteCarlo();
        double get_number_of_simulation () const ;
        void set_number_of_simulation(unsigned long int N) ;
        tuple<double, double>  pricer ( vanillaoptions * Option) ;

    protected:

    private:
        unsigned long int Number_of_simulation ;


};

#endif // MONTECARLO_H
