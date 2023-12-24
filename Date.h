#ifndef DATE_H
#define DATE_H
#include<iostream>
#include <ctime>
class Date
{
     public:

        Date();

        Date(int day, int month, int year);
        virtual ~Date();
        double period_diff();

     private :
         int year, month, day;

};

#endif // DATE_H
