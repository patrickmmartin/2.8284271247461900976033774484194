/*
 * root_classes.h
 *
 *  Created on: 28 May 2016
 *      Author: Patrick
 */

#ifndef ROOT_CLASSES_H_
#define ROOT_CLASSES_H_

#include "root_runner.h"

#include <math.h>

namespace {

double seed_root(double value) {
  int n = log10(value);

  return pow(10, n / 2);
}

} // end anonymous namespace

/**
 * class implementing calculating and logging closed form solution
 */
template <typename COUNTER = NullCounter> struct StdSqrt {
  double operator()(double value) {
    COUNTER counter;
    return counter(1, sqrt(value));
  };
};

/**
 * class implementing calculating and logging closed form solution
 */
template <typename COUNTER = NullCounter> struct ClosedForm {
  double operator()(double value) {
    COUNTER counter;
    return counter(1, exp(0.5 * log(value)));
  };
};

/**
 * class implementing calculating and logging Babylonian solution
 */
template <typename COUNTER = NullCounter> struct Bablyonian {
  double operator()(double value) {
    COUNTER counter;
    int n = 1;

    double x = seed_root(value);

    counter(n, x);
    while ((n < 1000) && (fabs((x * x) - value) > (value / 1E9))) {
      x = 0.5 * (x + (value / x));
      n++;
      counter(n, x);
    }
    return x;
  };
};

/**
 * class implementing calculating and logging Newton Raphson solution
 */
template <typename COUNTER = NullCounter> struct NewtonRaphsonCF {
  double operator()(double value) {
    COUNTER counter;
    int n = 1;

    long double x = seed_root(value);

    counter(n, x);
    while ((n < 1000) && (fabs((x * x) - value) > (value / 1E9))) {
      // x * x - value is the function for which we seek the root
      x = x - ((x * x - value) / (2 * x));
      n++;
      counter(n, x);
    }
    return x;
  };
};

/**
 * class implementing calculating and logging Newton Raphson solution
 */
template <typename COUNTER = NullCounter> struct NewtonRaphsonND {
  double operator()(double value) {
    COUNTER counter;
    int n = 1;

    long double x = seed_root(value);

    counter(n, x);
    while ((n < 1000) && (fabs((x * x) - value) > (value / 1E9))) {
      // x * x - value is the function for which we seek the root
      double gradient = (2 * x);
      x = x - ((x * x - value) / gradient);
      n++;
      counter(n, x);
    }
    return x;
  };
};

#endif /* ROOT_CLASSES_H_ */
