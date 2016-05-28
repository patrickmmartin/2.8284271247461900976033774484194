/*
 * root_classes.cpp
 *
 *  Created on: 28 May 2016
 *      Author: Patrick
 */

#include "root_runner.h"

#include <math.h>

namespace {
struct AlgoIds {
	static algo_id closed;
};

const char AlgoIds::closed[] = "closed";

}

template<> struct Algo<AlgoIds::closed> {
	double operator ()(double value) {
		return count(1, exp(0.5 * log(value)));
	}
	;
};

