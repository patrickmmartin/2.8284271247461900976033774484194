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

template <typename COUNTER = NullCounter> struct ClosedForm
{
	double operator ()(double value) {
		static COUNTER counter;
		return counter(1, exp(0.5 * log(value)));
	}
	;
};


#endif /* ROOT_CLASSES_H_ */
