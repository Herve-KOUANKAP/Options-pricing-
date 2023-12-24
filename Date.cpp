#include<iostream>
using namespace std;
#include "Date.h"
#include <ctime>

Date::Date()
{
    //ctor
}

Date::~Date()
{
    //dtor
}
Date::Date(int day, int month, int year)
{
  this->day = day;
  this->month = month;
  this->year = year;
}

double Date::period_diff()
{

  time_t now;
  struct tm * timeinfo;



  time ( &now );
  timeinfo = localtime ( &now );
  timeinfo->tm_year = year - 1900;
  timeinfo->tm_mon = month - 1;
  timeinfo->tm_mday = day;

  return difftime(mktime(timeinfo),now)/(60 * 60 * 24* 360); // donne la maturité année
}
