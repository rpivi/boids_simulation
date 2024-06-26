#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "birds.hpp"
#include "doctest.h"

//test for birds
/////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Testing the near function ") {
  // true
  SUBCASE("simple test") {
    double d = 50;
    birds::Boid p1{1., 0., 1., 1.};
    birds::Boid p2{1., 1., 1., 1.};
    CHECK(p2.near(p1, d) == true);
  }
  SUBCASE("test 1 ") {
    double d = 1.414213563;
    birds::Boid p1{0., 0., 0., 0.};
    birds::Boid p2{1., 1., 0., 0.};
    CHECK(p2.near(p1, d) == true);
  }
  SUBCASE("test 2 ") {
    double d = 1.414213563;
    birds::Boid p1{0., 0., 0., 0.};
    birds::Boid p2{1., 1., 0., 0.};
    CHECK(p1.near(p2, d) == true);
  }
  SUBCASE("test 3") {
    double d = 10.000000000001;
    birds::Boid p1{11., 1., 0., 0.};
    birds::Boid p2{3., 7., 0., 0.};
    CHECK(p2.near(p1, d) == true);
  }
  SUBCASE("test 4") {
    double d = 856.30894;
    birds::Boid p1{711., 610., 0., 0.};
    birds::Boid p2{40., 78., 0., 0.};
    CHECK(p2.near(p1, d) == true);
  }
  SUBCASE("test of two equal birds") {
    double d = 1;
    birds::Boid p1{40., 78., 0., 0.};
    birds::Boid p2{40., 78., 0., 0.};
    CHECK(p2.near(p1, d) == true);
  }
  // false
  SUBCASE("test of bird himself") {
    double d = 1;
    birds::Boid p1{711., 610., 0., 0.};
    CHECK(p1.near(p1, d) == false);
  }
  SUBCASE("simple test") {
    double d = 0.0001;
    birds::Boid p1{1., 0., 1., 1.};
    birds::Boid p2{1., 1., 1., 1.};
    CHECK(p2.near(p1, d) == false);
  }
  SUBCASE("test 1 ") {
    double d = 1.414213560;
    birds::Boid p1{0., 0., 0., 0.};
    birds::Boid p2{1., 1., 0., 0.};
    CHECK(p2.near(p1, d) == false);
  }
  SUBCASE("test 2 ") {
    double d = 1.414213560;
    birds::Boid p1{0., 0., 0., 0.};
    birds::Boid p2{1., 1., 0., 0.};
    CHECK(p1.near(p2, d) == false);
  }
  SUBCASE("test 3") {
    double d = 6.70820;
    birds::Boid p1{11., 1., 0., 0.};
    birds::Boid p2{3., 7., 0., 0.};
    CHECK(p2.near(p1, d) == false);
  }
  SUBCASE("test 4") {
    double d = 856.30891;
    birds::Boid p1{711., 610., 0., 0.};
    birds::Boid p2{40., 78., 0., 0.};
    CHECK(p2.near(p1, d) == false);
  }
}

TEST_CASE("Testing the update_v and update_p functions") {
  SUBCASE("simple test") {
    two_dim::vec v1{0., 0.};
    two_dim::vec v2{0., 0.};
    two_dim::vec v3{0., 0.};
    birds::Boid p1{1., 1., 1., 1.};
    double delta = 1.;
    p1.update_v(v1, v2, v3);
    p1.update_p(delta);
    CHECK(p1.get_v().x == 1.);
    CHECK(p1.get_v().y == 1.);
    CHECK(p1.get_p().x == 2.);
    CHECK(p1.get_p().y == 2.);
  }
  SUBCASE("test 1") {
    two_dim::vec v1{1., 6.};
    two_dim::vec v2{5., 8.};
    two_dim::vec v3{40., 6.};
    birds::Boid p1{1., 1., 700., 200.};
    double delta = 1. / 60.;
    p1.update_v(v1, v2, v3);
    p1.update_p(delta);
    CHECK(p1.get_v().x == 746.);
    CHECK(p1.get_v().y == 220.);
    CHECK(p1.get_p().x == 1. + 746. / 60);
    CHECK(p1.get_p().y == 1. + 220. / 60);
  }
  SUBCASE("test_ 2") {
    two_dim::vec v1{1., -6.};
    two_dim::vec v2{-5., 8.};
    two_dim::vec v3{40., -6.};
    double delta = 1. / 10;
    birds::Boid p1{800., 500., -700., 200.};
    p1.update_v(v1, v2, v3);
    p1.update_p(delta);
    CHECK(p1.get_v().x == -664.);
    CHECK(p1.get_v().y == 196.);
    CHECK(p1.get_p().x == 800. - 646. / 10);
    CHECK(p1.get_p().y == 500. + 196. / 10);
  }
}


//test for twodimensional
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    CHECK(p.x == 897.6);
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


TEST_CASE("Testing the distance function ") {
  SUBCASE("The distance from origin") {
    two_dim::vec p{0., 0.};
    two_dim::vec p2{3., 4.};
    CHECK(distance(p, p2) == 5.);
  }
  SUBCASE("sign test") {
    two_dim::vec p{0., 0.};
    two_dim::vec p2{3., 4.};
    CHECK(distance(p2, p) == 5.);
  }
  SUBCASE("0 distace test") {
    two_dim::vec p{1., 1.};
    two_dim::vec p2{1., 1.};
    CHECK(distance(p2, p) == 0.);
  }
  SUBCASE("test 1") {
    two_dim::vec p{3., 0.};
    two_dim::vec p2{0., 1.};
    CHECK(distance(p, p2) == doctest::Approx(3.16227));
  }
  SUBCASE("test 2") {
    two_dim::vec p{3., 0.};
    two_dim::vec p2{1., 1.};
    CHECK(distance(p, p2) == doctest::Approx(2.23606));
  }
}
