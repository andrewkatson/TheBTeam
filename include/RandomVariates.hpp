#pragma once
#include "rngs.hpp"
#include <cmath>
class RandomVariates{
public:
  RandomVariates();
  double Equilikely(double a, double b);
  double Geometric(double p);
  double Exponential(double m);
  double Uniform(double a, double b);

};
