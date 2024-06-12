#include "birds.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

namespace birds {
// get parameters
///////////////////////////////////////////////////////////////////////////////////////////

void set_parameters(double& num_boids, double& d, double& d_s, double& s,
                    double& a, double& c) {
  std::cout << "\n Insert the parameters \n the number of boids: ";
  std::cin >> num_boids;
  std::cout << "\n the near radius: ";
  std::cin >> d;
  std::cout << "\n the separation radius: ";
  std::cin >> d_s;
  std::cout << "\n the separation parameter: ";
  std::cin >> s;
  std::cout << "\n the allignement parameter: ";
  std::cin >> a;
  std::cout << "\n the cohesion parameter: ";
  std::cin >> c;
}

Boid::Boid(double posX, double posY, double velX, double velY)
    : position_{posX, posY}, velocity_{velX, velY} {}

// near function
bool Boid::near(Boid const& other, double d) const {
  if (this == &other) {
    return false;
  }
  if (distance(position_, other.position_) <= d) {
    return true;
  } else
    return false;
}

void Boid::update_v(two_dim::vec const& v1, two_dim::vec const& v2,
                    two_dim::vec const& v3) {
  velocity_ = velocity_ + v1 + v2 + v3;
}

void Boid::update_p(double delta_t) {
  assert(delta_t > 0);
  position_ = position_ + velocity_ * delta_t;
}

// toroidal space
void Boid::borders() {
  if (position_.x < 0) {
    position_.x += 900;
  } else if (position_.y < 0) {
    position_.y += 900;
  } else if (position_.x > 900) {
    position_.x -= 900;
  } else if (position_.y > 900) {
    position_.y -= 900;
  }
}

// center of mass
two_dim::vec Boid::center_mass(std::vector<Boid> const& flock,
                               double const& d) {
  two_dim::vec x_c{0., 0.};
  int n{0};
  x_c =
      std::accumulate(std::begin(flock), std::end(flock), two_dim::vec{0., 0.},
                      [&](two_dim::vec sum, const Boid other_b) {
                        if (near(other_b, d)) {
                          ++n;
                          return sum + other_b.get_p();
                        } else {
                          return sum;
                        }
                      });
  if (n > 1) {
    return x_c / n;
  }
  return x_c;
}

// 3 laws
two_dim::vec Boid::separation(std::vector<Boid> const& flock, double const& s,
                              double const& d_separation) {
  two_dim::vec v1{0., 0.};
  v1 = std::accumulate(std::begin(flock), std::end(flock), two_dim::vec{0., 0.},
                       [&](two_dim::vec sum, const Boid other_b) {
                         if (near(other_b, d_separation)) {
                           return sum + (other_b.get_p() - get_p());
                         } else {
                           return sum;
                         }
                       });
  return v1 * (-s);
}

two_dim::vec Boid::alignment(std::vector<Boid> const& flock, double const& a,
                             double const& d) {
  two_dim::vec v2{0., 0.};
  int n{0};
  v2 = std::accumulate(std::begin(flock), std::end(flock), two_dim::vec{0., 0.},
                       [&](two_dim::vec sum, const Boid other_b) {
                         if (near(other_b, d)) {
                           ++n;
                           return sum + other_b.get_v();
                         } else {
                           return sum;
                         }
                       });
  if (n > 1) {
    v2 = v2 / n;
    return (v2 - get_v()) * a;
  } else {
    return {0., 0.};
  }
}

two_dim::vec Boid::cohesion(std::vector<Boid> const& flock, double const& c,
                            double const& d) {
  two_dim::vec v3{0., 0.};
  two_dim::vec x_c = center_mass(flock, d);
  if (x_c.x == 0 && x_c.y == 0) {
    return v3;
  }
  v3 = (x_c - get_p()) * c;
  return v3;
}

double Flock::mean_position(std::vector<Boid> const& flock) {
  double mean_position{};
  mean_position =
      std::accumulate(std::begin(flock), std::end(flock), double{0.},
                      [&](double sum, const Boid b) {
                        sum += sqrt(pow(b.get_p().x, 2) + pow(b.get_p().y, 2));
                        return sum;
                      }) /
      static_cast<double>(std::size(flock));

  return mean_position;
}

double Flock::std_dev_p(std::vector<Boid> const& flock) {
  double std_dev_p{};
  double sum_p2{};
  sum_p2 = std::accumulate(std::begin(flock), std::end(flock), double{0.},
                           [&](double sum, Boid const& b) {
                             sum += (pow(b.get_p().x, 2) + pow(b.get_p().y, 2));
                             return sum;
                           });
  std_dev_p = sqrt((sum_p2 - static_cast<double>(std::size(flock)) *
                                 pow(Flock::mean_position(flock), 2)) /
                   (static_cast<double>(std::size(flock)) - 1));
  return std_dev_p;
}

}  // namespace birds
