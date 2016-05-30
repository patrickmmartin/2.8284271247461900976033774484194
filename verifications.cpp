/*
 * verifications.cpp
 *
 *  Created on: 29 May 2016
 *      Author: Patrick
 */

#include <cmath>

#include "eight_rooty_pieces.h"

#include "catch/catch.hpp"

#pragma GCC diagnostic ignored "-Wparentheses"

TEST_CASE("Square roots are computed (small range)", "[algorithms]") {

  for (int i = -5; i < 5; i += 1) {
    double arg = pow(10, i);
    CAPTURE(arg);
    auto std_sqrt = sqrt(arg);
    auto closed = my_sqrt(arg);
    auto bablyonian = my_sqrt_bablyonian(arg);
    auto newton = my_sqrt_newtonraphson(arg);
    auto range = my_sqrt_range(arg);
    auto naive = my_sqrt_naive(arg); // terribly inefficient
    auto DOOM = my_sqrt_homage_to_carmack(arg);

    // TODO(PMM) - check out the epsilon Approx uses
    REQUIRE(std_sqrt == Approx(closed));
    REQUIRE(std_sqrt == Approx(bablyonian));
    REQUIRE(std_sqrt == Approx(newton));
    REQUIRE(std_sqrt == Approx(range));
    REQUIRE(std_sqrt == Approx(naive));
    REQUIRE(std_sqrt == Approx(DOOM).epsilon(0.1));
  }
}

TEST_CASE("Square roots are computed (full range)", "[algorithms]") {

  // we can't call "naive" as way too slow
  for (double arg = std::numeric_limits<double>::min();
       arg < std::numeric_limits<double>::max(); arg *= 100) {
    CAPTURE(arg);
    auto std_sqrt = sqrt(arg);
    auto closed = my_sqrt(arg);
    auto bablyonian = my_sqrt_bablyonian(arg);
    auto newton = my_sqrt_newtonraphson(arg);
    auto range = my_sqrt_range(arg);

    REQUIRE(std_sqrt == Approx(closed));
    REQUIRE(std_sqrt == Approx(bablyonian));
    REQUIRE(std_sqrt == Approx(newton));
    REQUIRE(std_sqrt == Approx(range));
  }
}

TEST_CASE("Square roots are computed (denorm range)", "[algorithms]") {

  // http://stackoverflow.com/questions/20065406/whats-the-largest-denormalized-and-normalized-number64bit-iee-754-1985
  for (double arg = std::numeric_limits<double>::min();
       arg > std::numeric_limits<double>::denorm_min(); arg /= 10) {
    CAPTURE(arg);
    auto std_sqrt = sqrt(arg);
    auto closed = my_sqrt(arg);
    auto bablyonian = my_sqrt_bablyonian(arg);
    auto newton = my_sqrt_newtonraphson(arg);
    auto range = my_sqrt_range(arg);

    REQUIRE(std_sqrt == Approx(closed));
    REQUIRE(std_sqrt == Approx(bablyonian));
    REQUIRE(std_sqrt == Approx(newton));
    REQUIRE(std_sqrt == Approx(range).epsilon(0.001));
  }
}
