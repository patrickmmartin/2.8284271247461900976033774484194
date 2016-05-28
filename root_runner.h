/*
 * RootRunner.h
 *
 *  Created on: 28 May 2016
 *      Author: Patrick
 */

#ifndef ROOT_RUNNER_H_
#define ROOT_RUNNER_H_

/**
 * ID for the algo
 */
typedef char const algo_id[];

/**
 *
 */
struct NullCounter {
	double operator ()(int n, double value) {
		return value;
	}
};

/**
 * template implements the algorithm
 */
template<algo_id ALGO, typename COUNTER = NullCounter> struct Algo {
	COUNTER counter;
	double count(int n, double value) { return counter(n, value); }
	double operator()(double value); // not implemented
};

#endif /* ROOT_RUNNER_H_ */
