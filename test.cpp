#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "birds.hpp"
#include "doctest.h"

// test for birds
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
    CHECK(p1.get_v().x == doctest::Approx(143.874));
    CHECK(p1.get_v().y == doctest::Approx(42.4294));
    CHECK(p1.get_p().x == doctest::Approx(1. + 143.874 / 60));
    CHECK(p1.get_p().y == doctest::Approx(1. + 42.4294 / 60));
  }
  SUBCASE("test 2") {
    two_dim::vec v1{1., -6.};
    two_dim::vec v2{-5., 8.};
    two_dim::vec v3{40., -6.};
    double delta = 1. / 10.;
    birds::Boid p1{800., 500., -700., 200.};
    p1.update_v(v1, v2, v3);
    p1.update_p(delta);
    CHECK(p1.get_v().x == doctest::Approx(-143.863));
    CHECK(p1.get_v().y == doctest::Approx(42.4657));
    CHECK(p1.get_p().x == doctest::Approx(800. - 143.863 / 10));
    CHECK(p1.get_p().y == doctest::Approx(500. + 42.4657 / 10));
  }

  SUBCASE("test 3") {
    two_dim::vec v1{1., 0.};
    two_dim::vec v2{10., 10.};
    two_dim::vec v3{25., 0.};
    double delta = 1. / 30.;
    birds::Boid p1{0., 900., 10., 0.};
    p1.update_v(v1, v2, v3);
    p1.update_p(delta);
    CHECK(p1.get_v().x == 46.);
    CHECK(p1.get_v().y == 10.);
    CHECK(p1.get_p().x == doctest::Approx(46. / 30.));
    CHECK(p1.get_p().y == doctest::Approx(900. + 10. / 30.));
  }
}

TEST_CASE("Testing the center_mass function") {
  SUBCASE("simple test") {
    std::vector<birds::Boid> flock{{2., 2., 2., 2.}, {1., 1., 1., 1.}};
    double d{20.};
    birds::Boid c{0., 0., 0., 0.};
    CHECK(c.center_mass(flock, d).x == 1.5);
    CHECK(c.center_mass(flock, d).y == 1.5);
  }
  SUBCASE("test 1") {
    std::vector<birds::Boid> flock{
        {2., 2., 0., 0.}, {1., 1., 0., 0.}, {800., 850., 0., 0.}};
    double d{20.};
    birds::Boid c{801., 849., 0., 0.};
    CHECK(c.center_mass(flock, d).x == 800.);
    CHECK(c.center_mass(flock, d).y == 850.);
  }
  SUBCASE("test 2") {
    std::vector<birds::Boid> flock{{2., 2., 0., 0.},
                                   {1., 1., 0., 0.},
                                   {800., 850., 3., 0.},
                                   {802., 856., 0., 0.}};
    double d{20.};
    birds::Boid c{801., 849., 0., 0.};
    CHECK(c.center_mass(flock, d).x == 801.);
    CHECK(c.center_mass(flock, d).y == 853.);
  }
  SUBCASE("test 3") {
    std::vector<birds::Boid> flock{{2., 2., 0., 0.},     {1., 1., 0., 0.},
                                   {800., 850., 0., 0.}, {802., 856., 0., 0.},
                                   {803., 852., 0., 0.}, {810., 848., 0., 0.}};
    double d{20.};
    birds::Boid c{801., 849., 0., 0.};
    CHECK(c.center_mass(flock, d).x == 803.75);
    CHECK(c.center_mass(flock, d).y == 851.5);
  }
  SUBCASE("test 4") {
    std::vector<birds::Boid> flock{{2., 2., 0., 0.},     {1., 1., 0., 0.},
                                   {800., 850., 0., 0.}, {802., 856., 0., 0.},
                                   {803., 852., 0., 0.}, {810., 848., 0., 0.},
                                   {850., 848., 0., 0.}};
    double d{20.};
    birds::Boid c{801., 849., 0., 0.};
    CHECK(c.center_mass(flock, d).x == 803.75);
    CHECK(c.center_mass(flock, d).y == 851.5);
  }
  SUBCASE("test 5") {
    std::vector<birds::Boid> flock{
        {2., 2., 0., 0.},
        {1., 1., 0., 0.},
    };
    float d{20.};
    birds::Boid c{801., 849., 0., 0.};
    CHECK(c.center_mass(flock, d).x == 0.);
    CHECK(c.center_mass(flock, d).y == 0.);
  }
}

TEST_CASE("Testing the separation function") {
  SUBCASE("simple test") {
    std::vector<birds::Boid> flock{
        {2., 2., 2., 2.}, {2., 2., 2., 2.}, {2., 2., 2., 2.}};
    double d_separation{6};
    double s{0.02};
    birds::Boid boid{0., 0., 0., 0.};
    CHECK(boid.separation(flock, s, d_separation).x == -0.12);
    CHECK(boid.separation(flock, s, d_separation).y == -0.12);
  }
  SUBCASE("test 1") {
    std::vector<birds::Boid> flock{
        {50., 2., 2., 2.}, {4., 7., -20., 20.}, {2., 2., 70., -30.}};
    double d_separation{6};
    double s{0.02};
    birds::Boid boid{0., 0., 0., 0.};
    CHECK(boid.separation(flock, s, d_separation).x == -0.04);
    CHECK(boid.separation(flock, s, d_separation).y == -0.04);
  }
  SUBCASE("test 2") {
    std::vector<birds::Boid> flock{
        {50., 2., 2., 2.}, {4., 3., -20., 20.}, {2., 2., 70., -30.}};
    double d_separation{6};
    double s{0.02};
    birds::Boid boid{3., 3., 0., 0.};
    CHECK(boid.separation(flock, s, d_separation).x == 0.);
    CHECK(boid.separation(flock, s, d_separation).y == 0.02);
  }
  SUBCASE("test 3") {
    std::vector<birds::Boid> flock{{50., 2., 2., 2.},
                                   {4., 3., -20., 20.},
                                   {2., 2., 70., -30.},
                                   {4., 4., 70., -30.},
                                   {7., 10., 70., -30.}};
    double d_separation{20};
    double s{0.02};
    birds::Boid boid{3., 3., 1., 1.};
    CHECK(boid.separation(flock, s, d_separation).x == -0.1);
    CHECK(boid.separation(flock, s, d_separation).y == -0.14);
  }
  SUBCASE("test 4") {
    std::vector<birds::Boid> flock{{50., 2., 2., 2.},    {4., 3., -20., 20.},
                                   {2., 2., 70., -30.},  {4., 4., 70., -30.},
                                   {7., 10., 70., -30.}, {0., 0., 70., -30.}};
    double d_separation{20};
    double s{0.02};
    birds::Boid boid{3., 3., 100., -200.};
    CHECK(boid.separation(flock, s, d_separation).x == -0.04);
    CHECK(boid.separation(flock, s, d_separation).y == -0.08);
  }
}

TEST_CASE("testing the alignment function") {
  SUBCASE("simple test") {
    std::vector<birds::Boid> flock{{0., 0., 2., 2.}, {0., 0., 2., 2.}};
    double d{6.};
    double a{1.};
    birds::Boid boid{0., 0., 2., 2.};
    CHECK(boid.alignment(flock, a, d).x == 0.);
    CHECK(boid.alignment(flock, a, d).y == 0.);
  }
  SUBCASE("test 1") {
    std::vector<birds::Boid> flock{{50., 0., 2., 2.}, {0., 0., 3., 2.}};
    double d{6.};
    double a{1.};
    birds::Boid boid{0., 0., 2., 2.};
    CHECK(boid.alignment(flock, a, d).x == 1.);
    CHECK(boid.alignment(flock, a, d).y == 0.);
  }
  SUBCASE("test 2") {
    std::vector<birds::Boid> flock{
        {50., 0., 2., 2.}, {0., 0., 3., 2.}, {0., 1., 3., 2.}};
    double d{6.};
    double a{1.};
    birds::Boid boid{0., 0., 2., 2.};
    CHECK(boid.alignment(flock, a, d).x == 1.);
    CHECK(boid.alignment(flock, a, d).y == 0.);
  }
  SUBCASE("test 3") {
    std::vector<birds::Boid> flock{{50., 0., 2., 2.},
                                   {0., 0., 3., 2.},
                                   {0., 1., 3., 2.},
                                   {0., 1., 4., 2.}};
    double d{6.};
    double a{1.};
    birds::Boid boid{0., 0., 2., 2.};
    CHECK(boid.alignment(flock, a, d).x == doctest::Approx(4. / 3.));
    CHECK(boid.alignment(flock, a, d).y == 0.);
  }
  SUBCASE("test 4") {
    std::vector<birds::Boid> flock{{50., 0., 2., 2.}, {0., 0., 3., 2.},
                                   {0., 1., 3., 2.},  {0., 1., 4., 2.},
                                   {0., 30., 0., 4.}, {0., 0., 47., 60.}};
    double d{6.};
    double a{1.};
    birds::Boid boid{0., 0., 2., 2.};
    CHECK(boid.alignment(flock, a, d).x == 12.25);
    CHECK(boid.alignment(flock, a, d).y == 14.5);
  }
  SUBCASE("test 5") {
    std::vector<birds::Boid> flock{{50., 0., 2., 2.},   {0., 0., 3., 2.},
                                   {0., 1., 3., 2.},    {0., 1., 4., 2.},
                                   {0., 30., 0., 4.},   {1., 0., 47., 60.},
                                   {2., 3., -30., -20.}};
    double d{6};
    double a{0.5};
    birds::Boid boid{0., 0., 2., 2.};
    CHECK(boid.alignment(flock, a, d).x == doctest::Approx(1.7));
    CHECK(boid.alignment(flock, a, d).y == doctest::Approx(3.6));
  }
}
TEST_CASE("testing the cohesion function") {
  SUBCASE("simple test") {
    std::vector<birds::Boid> flock{{0., 0., 0., 0.}, {0., 0., 0., 0.}};
    double c{1.};
    double d{6.};
    birds::Boid boid{0., 0., 0., 0.};
    CHECK(boid.cohesion(flock, c, d).x == 0.);
    CHECK(boid.cohesion(flock, c, d).y == 0.);
  }
  SUBCASE("test 1") {
    std::vector<birds::Boid> flock{{3., 3., 0., 0.}, {4., 4., 0., 0.}};
    double c{1.};
    double d{6.};
    birds::Boid boid{0., 0., 0., 0.};
    CHECK(boid.cohesion(flock, c, d).x == 3.5);
    CHECK(boid.cohesion(flock, c, d).y == 3.5);
  }
  SUBCASE("test 2") {
    std::vector<birds::Boid> flock{
        {80., 3., 0., 0.}, {3., 3., 0., 0.}, {4., 4., 0., 0.}};
    double c{1.};
    double d{6.};
    birds::Boid boid{0., 0., 0., 0.};
    CHECK(boid.cohesion(flock, c, d).x == 3.5);
    CHECK(boid.cohesion(flock, c, d).y == 3.5);
  }
  SUBCASE("test 3") {
    std::vector<birds::Boid> flock{
        {80., 3., 0., 0.}, {3., 3., 0., 0.}, {4., 4., 0., 0.}};
    double c{1.};
    double d{20.};
    birds::Boid boid{8., 9., -40., 70.};
    CHECK(boid.cohesion(flock, c, d).x == -4.5);
    CHECK(boid.cohesion(flock, c, d).y == -5.5);
  }
  SUBCASE("test 4") {
    std::vector<birds::Boid> flock{{80., 3., -40., 0.},
                                   {3., 3., 0., 30.},
                                   {4., 4., 60., 200.},
                                   {7., 2., -10., 0.}};
    double c{0.5};
    double d{20.};
    birds::Boid boid{8., 9., -40., 70.};
    CHECK(boid.cohesion(flock, c, d).x == doctest::Approx(-5. / 3.));
    CHECK(boid.cohesion(flock, c, d).y == -3.);
  }
}
// test for statistics
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("testing the statistics functions") {
  SUBCASE("simple test") {
    birds::Flock flock_statistic;
    std::vector<birds::Boid> flock{{0., 0., 0., 0.}, {0., 0., 0., 0.}};
    flock_statistic.std_dev_p(flock);
    flock_statistic.std_dev_v(flock);
    CHECK(flock_statistic.mean_position(flock).x == 0);
    CHECK(flock_statistic.mean_position(flock).y == 0);
    CHECK(flock_statistic.std_dev_p(flock).x == 0);
    CHECK(flock_statistic.std_dev_p(flock).y == 0);
    CHECK(flock_statistic.mean_velocity(flock).x == 0);
    CHECK(flock_statistic.mean_velocity(flock).y == 0);
    CHECK(flock_statistic.std_dev_v(flock).x == 0);
    CHECK(flock_statistic.std_dev_v(flock).y == 0);
  }
  SUBCASE("test 1") {
    birds::Flock flock_statistic;
    std::vector<birds::Boid> flock{{1., 1., 1., 1.}, {1., 1., 1., 1.}};
    CHECK(flock_statistic.mean_position(flock).x == 1);
    CHECK(flock_statistic.mean_position(flock).y == 1);
    CHECK(flock_statistic.std_dev_p(flock).x == 0);
    CHECK(flock_statistic.std_dev_p(flock).y == 0);
    CHECK(flock_statistic.mean_velocity(flock).x == 1);
    CHECK(flock_statistic.mean_velocity(flock).y == 1);
    CHECK(flock_statistic.std_dev_v(flock).x == 0);
    CHECK(flock_statistic.std_dev_v(flock).y == 0);
  }
  SUBCASE("test 2") {
    birds::Flock flock_statistic;
    std::vector<birds::Boid> flock{{1., 1., 1., 1.}, {2., 2., 2., 2.}};
    CHECK(flock_statistic.mean_position(flock).x == 1.5);
    CHECK(flock_statistic.mean_position(flock).y == 1.5);
    CHECK(flock_statistic.std_dev_p(flock).x == 0.5);
    CHECK(flock_statistic.std_dev_p(flock).y == 0.5);
    CHECK(flock_statistic.mean_velocity(flock).x == 1.5);
    CHECK(flock_statistic.mean_velocity(flock).y == 1.5);
    CHECK(flock_statistic.std_dev_v(flock).x == 0.5);
    CHECK(flock_statistic.std_dev_v(flock).y == 0.5);
  }
}
// test for twodimensional
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
