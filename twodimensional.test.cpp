#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "twodimensional.hpp"

#include "doctest.h"

TEST_CASE("Testing the distance function ") {
  SUBCASE("The diagonal of a square") {
    two_dim::vec p1{0., 1.};
    two_dim::vec p2{1., 0.};
    CHECK(two_dim::distance(p1, p2) == doctest::Approx(1.4142));
  }
  SUBCASE("The same position") {
    two_dim::vec p{2., 3.};
    CHECK(two_dim::distance(p, p) == 0);
  }
  SUBCASE("Positive and negative vec") {
    two_dim::vec p1{4.5, 3.4};
    two_dim::vec p2{-1., -1.};
    CHECK(two_dim::distance(p1, p2) == doctest::Approx(7.0434));
  }
}

TEST_CASE("Testing the addition") {
  SUBCASE("Test null vec") {
    two_dim::vec p_null{0., 0.};
    two_dim::vec p{1., 1.};
    CHECK(distance(p, p_null + p) == 0);
  }
  SUBCASE("Test addition 1") {
    two_dim::vec p1{450., 320.};
    two_dim::vec p2{33.4, -430.};
    two_dim::vec p = p1 + p2;
    CHECK(p.x == 483.4);
    CHECK(p.y == -110.);
  }
  SUBCASE("Test additon 2") {
    two_dim::vec p1{900., 900.};
    two_dim::vec p2{-2.4, 67.};
    two_dim::vec p = p1 + p2;
    CHECK(p.x == 897.4);
    CHECK(p.y == 967.);
  }
}

TEST_CASE("Testing the norm function ") {
  SUBCASE("The norm of the null vec") {
    two_dim::vec p{0., 0.};
    CHECK(two_dim::norm(p) == 0);
  }
  SUBCASE("Test norm 1") {
    two_dim::vec p{230., 33.4};
    CHECK(two_dim::norm(p) == doctest::Approx(232.412));
  }
}