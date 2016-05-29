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
	double operator ()(int n, double value) {
		return value;
	}
};

/**
 * simple no-op counter suitable for interposing
 */
struct PrintingCounter {
	double operator ()(int n, double value) {
		std::cout << "[" << n << ", " << value <<"]\n";
		return value;
	}
};


#endif /* ROOT_RUNNER_H_ */
