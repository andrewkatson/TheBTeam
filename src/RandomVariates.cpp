#include "RandomVariates.hpp"


RandomVariates::RandomVariates(){}

//------------------------------------------------------------------------------
double  RandomVariates::Equilikely (double a, double b){
  /* ---------------------------------------------------
   * generate an Equilikely random variate, use a < b
   * ---------------------------------------------------
   */
	return (a+ (long) ((b-a+ 1) * Random()));
}


double RandomVariates::Geometric(double p)
/* ---------------------------------------------------
 * generate an Geometric random variate, use 0.0 < p < 1.0
 * ---------------------------------------------------
*/
{
return ((log(1.0 - Random()) / log(p)));
}

double RandomVariates::Exponential(double m)
/* ---------------------------------------------------
* generate an Exponential random variate, use m > 0.0
* ---------------------------------------------------
*/
{
return (-m * log(1.0 - Random()));
}


double RandomVariates::Uniform(double a, double b)
/* --------------------------------------------
* generate a Uniform random variate, use a < b
* --------------------------------------------
*/
{
return (a + (b - a) * Random());
}
