/*
 * verifications.cpp
 *
 *  Created on: 29 May 2016
 *      Author: Patrick
 */

#include <math.h>

#include "eight_rooty_pieces.h"

#include "catch/catch.hpp"

TEST_CASE( "Square roots are computed (small range)", "[algorithms]" ) {

	for (int i = -5; i < 5; i += 1) {
		double arg = pow(10, i);
		INFO(arg);
		auto std_sqrt = sqrt(arg);
		auto closed = my_sqrt(arg);
		auto bablyonian = my_sqrt_bablyonian(arg);
		auto newton = my_sqrt_newtonraphson(arg);
		auto range = my_sqrt_range(arg);
		auto naive = my_sqrt_naive(arg); // terribly inefficient
		auto DOOM = my_sqrt_homage_to_carmack(arg);

		// TODO(PMM) - check out the epsilon Approx uses
		REQUIRE( std_sqrt == Approx(closed) );
		REQUIRE( std_sqrt == Approx(bablyonian) );
		REQUIRE( std_sqrt == Approx(newton) );
		REQUIRE( std_sqrt == Approx(range) );
		REQUIRE( std_sqrt == Approx(naive) );
		REQUIRE( std_sqrt == Approx(DOOM).epsilon(0.1) );

	}

}


TEST_CASE( "Square roots are computed (full range)", "[algorithms]" ) {

	// we can't call naive as way too slow
	for (int i = -308; i < 308; i += 10) {
		double arg = pow(10, i);
		auto std_sqrt = sqrt(arg);
		auto closed = my_sqrt(arg);
		auto bablyonian = my_sqrt_bablyonian(arg);
		auto newton = my_sqrt_newtonraphson(arg);
//		auto range = my_sqrt_range(arg);

		// TODO(PMM) - check out the epsilon Approx uses
		REQUIRE( std_sqrt == Approx(closed) );
		REQUIRE( std_sqrt == Approx(bablyonian) );
		REQUIRE( std_sqrt == Approx(newton) );
//		REQUIRE( std_sqrt == Approx(range).epsilon(0.001) ); // TODO(PMM) something fishy there

	}

}

