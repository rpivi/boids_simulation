#include "birds.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>

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
  std::cout << "\n the alignement parameter: ";
  std::cin >> a;
  std::cout << "\n the cohesion parameter: ";
  std::cin >> c;

  if (num_boids < 0 || d < 0 || d_s < 0 || s < 0 || a < 0 || c < 0) {
    throw std::runtime_error("Invalid parameter");
  }
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

  // maximum velocity
  if (two_dim::norm(velocity_) > 150.) {
    double const angle{std::atan2(velocity_.y, velocity_.x)};
    velocity_.x = 150. * std::cos(angle);
    velocity_.y = 150. * std::sin(angle);
  }
}

void Boid::update_p(double delta_t) {
  if (delta_t < 0) {
    throw std::runtime_error("Invalid parameter");
  }
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
  if (n >= 1) {
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

two_dim::vec Flock::mean_position(std::vector<Boid> const& flock) {
  auto N = static_cast<double>(std::size(flock));

  mean_position_.x =
      std::accumulate(std::begin(flock), std::end(flock), double{0.},
                      [&](double sum, const Boid b) {
                        sum += b.get_p().x;
                        return sum;
                      }) /
      N;

  mean_position_.y =
      std::accumulate(std::begin(flock), std::end(flock), double{0.},
                      [&](double sum, const Boid b) {
                        sum += b.get_p().y;
                        return sum;
                      }) /
      N;
  return mean_position_;
}

two_dim::vec Flock::std_dev_p(std::vector<Boid> const& flock) {
  two_dim::vec sum_p2{};
  sum_p2.x = std::accumulate(std::begin(flock), std::end(flock), double{0.},
                             [&](double sum, Boid const& b) {
                               sum += pow(b.get_p().x - mean_position_.x, 2);
                               return sum;
                             });

  sum_p2.y = std::accumulate(std::begin(flock), std::end(flock), double{0.},
                             [&](double sum, Boid const& b) {
                               sum += pow(b.get_p().y - mean_position_.y, 2);
                               return sum;
                             });

  auto N = static_cast<double>(std::size(flock));

  standard_dev_position_.x = sqrt(sum_p2.x / ((N - 1) * N));

  standard_dev_position_.y = sqrt(sum_p2.y / ((N - 1) * N));

  return standard_dev_position_;
}

two_dim::vec Flock::mean_velocity(std::vector<Boid> const& flock) {
  auto N = static_cast<double>(std::size(flock));

  mean_velocity_.x =
      std::accumulate(std::begin(flock), std::end(flock), double{0.},
                      [&](double sum, const Boid b) {
                        sum += b.get_v().x;
                        return sum;
                      }) /
      N;

  mean_velocity_.y =
      std::accumulate(std::begin(flock), std::end(flock), double{0.},
                      [&](double sum, const Boid b) {
                        sum += b.get_v().y;
                        return sum;
                      }) /
      N;

  return mean_velocity_;
}

two_dim::vec Flock::std_dev_v(std::vector<Boid> const& flock) {
  auto N = static_cast<double>(std::size(flock));
  two_dim::vec sum_v2{};
  sum_v2.x = std::accumulate(std::begin(flock), std::end(flock), double{0.},
                             [&](double sum, Boid const& b) {
                               sum += pow(b.get_v().x - mean_velocity_.x, 2);
                               return sum;
                             });

  sum_v2.y = std::accumulate(std::begin(flock), std::end(flock), double{0.},
                             [&](double sum, Boid const& b) {
                               sum += pow(b.get_v().y - mean_velocity_.y, 2);
                               return sum;
                             });

  standard_dev_velocity_.x = sqrt(sum_v2.x / (N * (N - 1)));

  standard_dev_velocity_.y = sqrt(sum_v2.y / (N * (N - 1)));

  return standard_dev_velocity_;
}

}  // namespace birds
