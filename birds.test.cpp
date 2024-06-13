#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "birds.hpp"

#include "doctest.h"

TEST_CASE("Testing the near function ") {
  //true
  SUBCASE("simple test") {
    double d = 50;
    birds::Boid p1{1., 0.,1.,1.};
    birds::Boid p2{1., 1., 1., 1.};
    CHECK (p2.near(p1 , d)==true);
  }
  SUBCASE("test 1 ") {
    double d = 1.414213563;
    birds::Boid p1{0., 0.,0.,0.};
    birds::Boid p2{1., 1., 0., 0.};
    CHECK (p2.near(p1 , d)==true);
  }
  SUBCASE("test 2 ") {
    double d = 1.414213563;
    birds::Boid p1{0., 0.,0.,0.};
    birds::Boid p2{1., 1., 0., 0.};
    CHECK (p1.near(p2 , d)==true);
  }
  SUBCASE("test 3") {
    double d = 6.708204;
    birds::Boid p1{11., 1.,0.,0.};
    birds::Boid p2{3., 7., 0., 0.};
    CHECK (p2.near(p1 , d)==true);
  }
  SUBCASE("test 4") {
    double d = 856.30894;
    birds::Boid p1{711., 610.,0.,0.};
    birds::Boid p2{40., 78., 0., 0.};
    CHECK (p2.near(p1 , d)==true);
  }
  SUBCASE("test of two equal birds") {
    double d = 1;
    birds::Boid p1{40., 78., 0., 0.};
    birds::Boid p2{40., 78., 0., 0.};
    CHECK (p2.near(p1 , d)==true);
  }
  //false
  SUBCASE("test of bird himself") {
    double d = 1;
    birds::Boid p1{711., 610.,0.,0.};
    CHECK (p1.near(p1 , d)==false);
  }
   SUBCASE("simple test") {
    double d = 0.0001;
    birds::Boid p1{1., 0.,1.,1.};
    birds::Boid p2{1., 1., 1., 1.};
    CHECK (p2.near(p1 , d)==false);
  }
  SUBCASE("test 1 ") {
    double d = 1.414213560;
    birds::Boid p1{0., 0.,0.,0.};
    birds::Boid p2{1., 1., 0., 0.};
    CHECK (p2.near(p1 , d)==false);
  }
  SUBCASE("test 2 ") {
    double d = 1.414213560;
    birds::Boid p1{0., 0.,0.,0.};
    birds::Boid p2{1., 1., 0., 0.};
    CHECK (p1.near(p2 , d)==false);
  }
  SUBCASE("test 3") {
    double d = 6.70820;
    birds::Boid p1{11., 1.,0.,0.};
    birds::Boid p2{3., 7., 0., 0.};
    CHECK (p2.near(p1 , d)==false);
  }
  SUBCASE("test 4") {
    double d = 856.30891;
    birds::Boid p1{711., 610.,0.,0.};
    birds::Boid p2{40., 78., 0., 0.};
    CHECK (p2.near(p1 , d)==false);
  } 
}

//get p
//get v

TEST_CASE("Testing the update_v and update_p functions") {

  SUBCASE("simple test") {
    two_dim::vec v1 {0. ,0.};
    two_dim::vec v2 {0. ,0.};
    two_dim::vec v3 {0. ,0.};
    birds::Boid p1{1., 1., 1., 1.};
    double delta=1;
    p1.update_v(v1 , v2, v3);
    p1.update_p(delta);
    CHECK (p1.get_v().x==1 && p1.get_v().y==1);
    CHECK(p1.get_p().x==1 && p1.get_p().y==1);
  }
  SUBCASE("test 1") {
    two_dim::vec v1 {1. ,6.};
    two_dim::vec v2 {5. ,8.};
    two_dim::vec v3 {40. ,6.};
    birds::Boid p1{1., 1., 700., 200.};
    double delta=1/60;
    p1.update_v(v1 , v2, v3);
    p1.update_p(delta);
    CHECK (p1.get_v().x==746 && p1.get_v().y==220);
    CHECK (p1.get_p().x==1+746/60 && p1.get_p().y==1+220/60);
  }
  SUBCASE("test 1") {
    two_dim::vec v1 {1. ,-6.};
    two_dim::vec v2 {-5. ,8.};
    two_dim::vec v3 {40. ,-6.};
    birds::Boid p1{1., 1., -700., 200.};
    p1.update_v(v1 , v2, v3);
    CHECK (p1.get_v().x==-664 && p1.get_v().y==196);
  }
}