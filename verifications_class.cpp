/*
 * verifications_class.cpp
 *
 *  Created on: 29 May 2016
 *      Author: Patrick
 */

#include <math.h>

#include "catch/catch.hpp"

#include "root_classes.h"

TEST_CASE( "Std matches closed form", "[classes]" ) {

	// we can't call naive as way too slow
	for (int i = -308; i < 308; i += 10) {
		double arg = pow(10, i);
		REQUIRE( sqrt(arg) == Approx(ClosedForm<>()(arg)) ); // note ultra small values are an issue!

	}

}






