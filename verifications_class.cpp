/*
 * verifications_class.cpp
 *
 *  Created on: 29 May 2016
 *      Author: Patrick
 */

#include <math.h>

#include "catch/catch.hpp"

#include "root_classes.h"

#pragma GCC diagnostic ignored "-Wparentheses"

// std::numeric_limits<double>::denorm_min()   4.94066e-324
// std::numeric_limits<double>::min()          2.22507e-308

TEST_CASE("Std matches closed form", "[classes]") {

  for (double arg = std::numeric_limits<double>::min();
       arg < std::numeric_limits<double>::max(); arg *= 100) {
    CAPTURE(arg);
    REQUIRE(sqrt(arg) == Approx(ClosedForm<>()(arg)));
  }
}

TEST_CASE("Std matches closed form for denorm range", "[classes]") {

  for (double arg = std::numeric_limits<double>::denorm_min();
       arg < std::numeric_limits<double>::min(); arg *= 10) {
    CAPTURE(arg);
    REQUIRE(sqrt(arg) == Approx(ClosedForm<>()(arg)));
  }
}

TEST_CASE("Std matches babylonian", "[classes]") {

  for (double arg = std::numeric_limits<double>::min();
       arg < std::numeric_limits<double>::max(); arg *= 100) {
    CAPTURE(arg);
    REQUIRE(sqrt(arg) == Approx(Bablyonian<>()(arg)));
  }
}

TEST_CASE("Std matches babylonian for denorm range", "[classes]") {

  for (double arg = std::numeric_limits<double>::min();
       arg > std::numeric_limits<double>::denorm_min(); arg /= 10) {
    CAPTURE(arg);
    REQUIRE(sqrt(arg) == Approx(Bablyonian<>()(arg)));
  }
}

TEST_CASE("Std matches Newton Raphson CF", "[classes]") {

  for (double arg = std::numeric_limits<double>::min();
       arg < std::numeric_limits<double>::max(); arg *= 100) {
    CAPTURE(arg);
    REQUIRE(sqrt(arg) == Approx(NewtonRaphsonCF<>()(arg)));
  }
}

TEST_CASE("Std matches Newton Raphson CF for denorm range", "[classes]") {

  for (double arg = std::numeric_limits<double>::min();
       arg > std::numeric_limits<double>::denorm_min(); arg /= 10) {
    CAPTURE(arg);
    REQUIRE(sqrt(arg) == Approx(NewtonRaphsonCF<>()(arg)));
  }
}

TEST_CASE("Std matches Newton Raphson ND", "[classes]") {

  for (double arg = std::numeric_limits<double>::min();
       arg < std::numeric_limits<double>::max(); arg *= 100) {
    CAPTURE(arg);
    REQUIRE(sqrt(arg) == Approx(NewtonRaphsonND<>()(arg)));
  }
}

TEST_CASE("Std matches Newton Raphson ND for denorm range", "[classes]") {

  for (double arg = std::numeric_limits<double>::min();
       arg > std::numeric_limits<double>::denorm_min(); arg /= 10) {
    CAPTURE(arg);
    REQUIRE(sqrt(arg) == Approx(NewtonRaphsonND<>()(arg)));
  }
}

TEST_CASE("Newton Raphson CF matches Newton Raphson ND", "[classes]") {

  for (double arg = std::numeric_limits<double>::min();
       arg < std::numeric_limits<double>::max(); arg *= 100) {
    CAPTURE(arg);
    REQUIRE(NewtonRaphsonCF<>()(arg) == NewtonRaphsonND<>()(arg));
  }
}

TEST_CASE("Newton Raphson CF matches Newton Raphson ND for denorm range",
          "[classes]") {

  for (double arg = std::numeric_limits<double>::min();
       arg > std::numeric_limits<double>::denorm_min(); arg /= 10) {
    CAPTURE(arg);
    REQUIRE(NewtonRaphsonCF<>()(arg) == NewtonRaphsonND<>()(arg));
  }
}

TEST_CASE("Std matches Range Reduction", "[classes]") {

  for (double arg = std::numeric_limits<double>::min();
       arg < std::numeric_limits<double>::max(); arg *= 100) {
    CAPTURE(arg);
    REQUIRE(sqrt(arg) == Approx(BisectionSearch<>()(arg)));
  }
}

TEST_CASE("Std matches Range Reduction for denorm range", "[classes]") {

  for (double arg = std::numeric_limits<double>::min();
       arg > std::numeric_limits<double>::denorm_min(); arg /= 10) {
    CAPTURE(arg);
    REQUIRE(sqrt(arg) == Approx(BisectionSearch<>()(arg)));
  }
}

TEST_CASE("Std matches Quake64", "[classes]") {

  for (double arg = std::numeric_limits<double>::min();
       arg < std::numeric_limits<double>::max(); arg *= 100) {
    CAPTURE(arg);
    REQUIRE(sqrt(arg) == Approx(Inverse<>()(arg)));
  }
}

TEST_CASE("Std matches Quake64 for denorm Range", "[classes]") {

  for (double arg = std::numeric_limits<double>::min();
       arg > std::numeric_limits<double>::denorm_min(); arg /= 10) {
    CAPTURE(arg);
    REQUIRE(sqrt(arg) == Approx(Inverse<>()(arg)));
  }
}

// the following two take a stunning amount of time

// TEST_CASE("Std matches Sweep and Step", "[classes]") {
//
//  for (double arg = std::numeric_limits<double>::min();
//       arg < std::numeric_limits<double>::max(); arg *= 100000000) {
//    CAPTURE(arg);
//    REQUIRE(sqrt(arg) == Approx(ScanAndStep<>()(arg)));
//  }
//}

// TEST_CASE("Std matches Sweep and Step for denorm range", "[classes]") {
//
//  for (double arg = std::numeric_limits<double>::min();
//       arg > std::numeric_limits<double>::denorm_min(); arg /= 10) {
//    CAPTURE(arg);
//    REQUIRE(sqrt(arg) == Approx(ScanAndStep<>()(arg)));
//  }
//}
