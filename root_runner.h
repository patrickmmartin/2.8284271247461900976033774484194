/*
 * RootRunner.h
 *
 *  Created on: 28 May 2016
 *      Author: Patrick
 */

#ifndef ROOT_RUNNER_H_
#define ROOT_RUNNER_H_

#include <iostream>

/**
 * ID for the algo
 */
typedef char const algo_id[];

/**
 * simple no-op counter suitable for interposing
 */
struct NullCounter {
  double operator()(int n, double value) { return value; }
};

/**
 * simple no-op counter suitable for interposing for range algorithms
 */
struct NullRangeCounter {
  double operator()(int n, double lower, double upper) { return upper; }
};

/**
 * simple printer for logging iterations
 */
struct PrintingCounter {
  double operator()(int n, double value) {
    std::cout << n << ", " << value << "\n";
    return value;
  }
};

/**
 * simple printer for logging iterations of range algorithms
 */
struct PrintingRangeCounter {
  double operator()(int n, double lower, double upper) {
    std::cout << n << ", " << lower << ", " << upper << "\n";
    return upper;
  }
};

/**
 * simple printer for logging final result and n
 */
struct SummaryCounter {
  int _n;
  double _value;
  double operator()(int n, double value) {
    _n = n;
    _value = value;
    return value;
  }
  ~SummaryCounter() { std::cout << "[" << _n << ", " << _value << "]\n"; }
};

/**
 * simple printer for logging final result and n
 */
struct SummaryRangeCounter {
  int _n;
  double _lower, _upper;
  double operator()(int n, double lower, double upper) {
    _n = n;
    _lower = lower;
    _upper = upper;
    return upper;
  }
  ~SummaryRangeCounter() {
    std::cout << _n << ", " << _lower << ", " << _upper << "\n";
  }
};

#endif /* ROOT_RUNNER_H_ */
