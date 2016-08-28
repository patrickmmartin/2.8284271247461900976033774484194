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

constexpr double TOLERANCE = 1E-9;
constexpr int ITERATIONS = 30;
constexpr int RANGE_ITERATIONS = 100;

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
    while ((n < ITERATIONS) && (fabs((x * x) - value) > (value * TOLERANCE))) {
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
    while ((n < ITERATIONS) && (fabs((x * x) - value) > (value * TOLERANCE))) {
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
    while ((n < ITERATIONS) && (fabs((x * x) - value) > (value * TOLERANCE))) {
      // x * x - value is the function for which we seek the root
      long double gradient =
          (((x * 1.5) * (x * 1.5)) - ((x * 0.5) * (x * 0.5))) / (x);
      x = x - ((x * x - value) / gradient);
      n++;
      counter(n, x);
    }
    return x;
  };
};

/**
 * class implementing range reduction solution
 */
template <typename COUNTER = NullRangeCounter> struct BisectionSearch {
  double operator()(double value) {
    COUNTER counter;

    double upper = seed_root(value) * 10;
    double lower = seed_root(value) / 10;

    double x = (lower + upper) / 2;

    int n = 1;

    while ((n < RANGE_ITERATIONS) &&
           (fabs((x * x) - value) > (value * TOLERANCE))) {

      counter(n, lower, upper);

      if (((x * x) > value))
        upper = x;
      else
        lower = x;

      x = (lower + upper) / 2;
      n++;
    }

    return x;
  };
};

/**
 * class implementing step reduction solution
 */
template <typename COUNTER = NullRangeCounter> struct ScanAndStep {
  double operator()(double value) {
    COUNTER counter;

    int n = 1;
    double x = seed_root(value) / 2;
    double step = x / 4;
    double lastdiff = 0;
    double diff = (x * x) - value;

    while ((n < RANGE_ITERATIONS) && (fabs(diff) > (value * TOLERANCE))) {
      if (diff > 0)
        x -= step;
      else
        x += step;

      counter(n, x, step);

      if ((diff > 0) != (lastdiff > 0)) {
        step = step * 0.50;
      }
      lastdiff = diff;
      diff = (x * x) - value;
      n++;
    }

    return x;
  };
};

/**
 * class implementing inverse square root solution with the good initial guess
 */
template <typename COUNTER = NullCounter> struct Inverse {
  double operator()(double value) {
    COUNTER counter;
    long long i, r;
    double x2 = value * 0.5, y = value;
    i = *(long long *)&y;
    i = 0x5fe6eb50c7b537a9 - (i >> 1);
    y = *(double *)&i;
    for (r = 0; r < 10; r++) {
      counter(1, value * y);
      y = y * (1.5 - (x2 * y * y));
    }
    return counter(1, value * y);
  };
};

#endif /* ROOT_CLASSES_H_ */
