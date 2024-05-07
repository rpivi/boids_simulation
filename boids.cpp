#include <SFML/Graphics.hpp>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>

// constant value
///////////////////////////////////////////////////////////////////////////////////////////
const double frame{60};
const double delta{1 / frame};

// random generation of number
///////////////////////////////////////////////////////////////////////////////////////////
std::default_random_engine eng;
std::uniform_real_distribution<> dis(250., 600.0);
std::uniform_real_distribution<> dis2(-1., 1.);

// get parameters
///////////////////////////////////////////////////////////////////////////////////////////

void set_parameters(double& num_boids, double& d, double& d_s, double& s,
                    double& a, double& c) {
  std::cout << "\n Insert the parameters \n the number of boids: ";
  std::cin >> num_boids;
  std::cout << "\n the near radius:";
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

// two dimensional rappresentation
////////////////////////////////////////////////////////////////////////////////////////////
struct two_d {
  double x;
  double y;
};

// overloading operator
two_d operator+(two_d const& a, two_d const& b) {
  return two_d{a.x + b.x, a.y + b.y};
}
two_d operator-(two_d const& a, two_d const& b) {
  return two_d{a.x - b.x, a.y - b.y};
}
two_d operator*(two_d const& a, double const& b) {
  return two_d{a.x * b, a.y * b};
}

// Boid
// //////////////////////////////////////////////////////////////////////////////////////////
class Boid {
 private:
  two_d position_;
  two_d velocity_;

 public:
  Boid()  // random number by default
      : position_{dis(eng), dis(eng)}, velocity_{dis2(eng), dis2(eng)} {}

  two_d get_p() const { return position_; }
  two_d get_v() const { return velocity_; }

  bool near(Boid const& other, double radius) const {
    if (position_.x == other.position_.x && position_.y == other.position_.y) {
      return false;
    }
    if (std::sqrt(pow(position_.x - other.position_.x, 2) +
                  pow(position_.y - other.position_.y, 2)) <= radius) {
      return true;
    } else
      return false;
  }

  void update_v(two_d const& v1, two_d const& v2, two_d const& v3) {
    velocity_ = velocity_ + v1 + v2 + v3;
  }

  void update_p(double delta_t) {
    assert(delta_t > 0);
    position_ = position_ + velocity_ * delta_t;
  }

  void borders() {
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
};

// center of mass
////////////////////////////////////////////////////////////////////////////////////////////
two_d center_mass(std::vector<Boid> const& flock, Boid const& bird,
                  double const& r) {
  two_d x_c{0., 0.};
  int n{0};
  for (auto& other_b : flock) {
    if (bird.near(other_b, r)) {
      ++n;
      x_c = x_c + other_b.get_p();
    }
  }
  if (n > 1) {
    return x_c * (1. / (n));
  }
  return x_c;
}

// 3 laws
/////////////////////////////////////////////////////////////////////////////////////////////
two_d separation(Boid const& bird, std::vector<Boid> const& flock,
                 double const& s, double const& r_separation) {
  two_d v1{0., 0.};
  for (auto& other_b : flock) {
    if (bird.near(other_b, r_separation)) {
      v1 = (other_b.get_p() - bird.get_p()) + v1;
    }
  }
  return v1 * (-s);
}
two_d alignment(Boid const& bird, std::vector<Boid> const& flock,
                double const& a, double const& r) {
  two_d v2{0., 0.};
  int n{0};
  for (auto& other_b : flock) {
    if (bird.near(other_b, r)) {
      ++n;
      v2 = other_b.get_v() + v2;
    }
  }
  if (n > 1) {
    v2 = v2 * (1. / (n));
    return (v2 - bird.get_v()) * a;
  } else {
    return {0., 0.};
  }
}
two_d cohesion(Boid const& bird, std::vector<Boid> const& flock,
               double const& c, double const& r) {
  two_d v3{0., 0.};
  two_d x_c = center_mass(flock, bird, r);
  if (x_c.x == 0 && x_c.y == 0) {
    return v3;
  }
  v3 = (x_c - bird.get_p()) * c;
  return v3;
}

// Main
int main() {
  double num_boids{0.};
  double d_s{0.};
  double d{0.};
  double s{0.};
  double a{0.};
  double c{0.};
  set_parameters(num_boids, d, d_s, s, a, c);

  // creation of the flock
  std::vector<Boid> flock;
  for (int i = 0; i < num_boids; ++i) {
    flock.push_back(Boid());
  }

  // graphics
  sf::RenderWindow window(sf::VideoMode(900, 900), "Boids");
  window.setFramerateLimit(frame);
  // setting the framerate

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear();
    for (auto& boid : flock) {
      // The circle rappresent a boid
      sf::CircleShape circle(2);
      boid.update_v(separation(boid, flock, s, d_s),
                    alignment(boid, flock, a, d), cohesion(boid, flock, c, d));
      boid.update_p(delta);
      boid.borders();

      // Setting the position of the circle
      circle.setPosition(boid.get_p().x, boid.get_p().y);

      // Boids are blue for me
      circle.setFillColor(sf::Color::Blue);
      window.draw(circle);
    }
    window.display();
  }
}
