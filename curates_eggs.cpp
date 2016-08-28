#include "catch/catch.hpp"

TEST_CASE("float values are sorted as integers", "oddities") {

  long const zero = 0;
  float prior = *(float *)&zero;

  for (long i = 1; i != std::numeric_limits<long>::max(); i++) {
    float y = *(float *)&i;

    CHECK(y > prior);
    prior = y;
  }
}


// could take several months?
//TEST_CASE("double values are sorted as integers", "oddities") {
//
//  long long const zero = 0;
//  double prior = *(float *)&zero;
//
//  for (long long i = 1; i != std::numeric_limits<long long>::max(); i++) {
//    double y = *(double *)&i;
//
//    CHECK(y > prior);
//    prior = y;
//  }
//}
