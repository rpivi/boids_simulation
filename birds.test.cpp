#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "birds.hpp"

#include "doctest.h"

TEST_CASE("Testing the near function ") {
  SUBCASE("The diagonal of a square") {
    double d = 50;
    birds::Boid p1{1., 0.,1.,1.};
    birds::Boid p2{1., 1., 1., 1.};
    CHECK( birds::Boid::near(p1 , d)const==true);
  }
}

