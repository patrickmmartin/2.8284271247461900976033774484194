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
 * simple printer for logging iterations
 */
struct PrintingCounter {
  double operator()(int n, double value) {
    std::cout << n << ", " << value;
    return value;
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
  ~SummaryCounter() { std::cout << _n << ", " << _value; }
};

#endif /* ROOT_RUNNER_H_ */
