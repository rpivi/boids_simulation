#include <SFML/Graphics.hpp>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>

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

// two dimensional rappresentation
////////////////////////////////////////////////////////////////////////////////////////////
struct vec {
  double x;
  double y;
};
// overloading operator
vec operator+(vec const& a, vec const& b) { return vec{a.x + b.x, a.y + b.y}; }
vec operator-(vec const& a, vec const& b) { return vec{a.x - b.x, a.y - b.y}; }
vec operator*(vec const& a, double const& b) { return vec{a.x * b, a.y * b}; }
vec operator/(vec const& a, int b) { return vec{a.x / b, a.y / b}; }

// norm and distance function
double norm(vec const& p) { return std::hypot(p.x, p.y); }

double distance(vec const& p, vec const& otherp) {
  vec difference = p - otherp;
  return norm(difference);
}

// Boid
/////////////////////////////////////////////////////////////////////////////////////////////
class Boid {
 private:
  vec position_;
  vec velocity_;

 public:
  // Constructor
  Boid(double posX, double posY, double velX, double velY)
      : position_{posX, posY}, velocity_{velX, velY} {}

  vec get_p() const { return position_; }
  vec get_v() const { return velocity_; }

  // near function
  bool near(Boid const& other, double d) const {
    if (this == &other) {
      return false;
    }
    if (distance(position_, other.position_) <= d) {
      return true;
    } else
      return false;
  }

  void update_v(vec const& v1, vec const& v2, vec const& v3) {
    velocity_ = velocity_ + v1 + v2 + v3;
  }

  void update_p(double delta_t) {
    assert(delta_t > 0);
    position_ = position_ + velocity_ * delta_t;
  }

  // toroidal space
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

  // center of mass
  /* vec center_mass(std::vector<Boid> const& flock, double const& d) {
     vec x_c{0., 0.};
     int n{0};
     for (auto& other_b : flock) {
       if (near(other_b, d)) {
         ++n;
         x_c = x_c + other_b.get_p();
       }
     }
     if (n > 1) {
       return x_c / n;
     }
     return x_c;
   }*/
  vec center_mass(std::vector<Boid> const& flock, double const& d) {
    vec x_c{0., 0.};
    int n{0};
    x_c = std::accumulate(std::begin(flock), std::end(flock), vec{0., 0.},
                          [&](vec sum, const Boid other_b) {
                            if (near(other_b, d)) {
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
  vec separation(std::vector<Boid> const& flock, double const& s,
                 double const& d_separation) {
    vec v1{0., 0.};

    v1 = std::accumulate(std::begin(flock), std::end(flock), vec{0., 0.},
                         [&](vec sum, const Boid other_b) {
                           if (near(other_b, d_separation)) {
                             return sum + (other_b.get_p() - get_p());
                           } else {
                             return sum;
                           }
                         });
    return v1 * (-s);
  }

  vec alignment(std::vector<Boid> const& flock, double const& a,
                double const& d) {
    vec v2{0., 0.};

    int n{0};

    v2 = std::accumulate(std::begin(flock), std::end(flock), vec{0., 0.},
                         [&](vec sum, const Boid other_b) {
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

  vec cohesion(std::vector<Boid> const& flock, double const& c,
               double const& d) {
    vec v3{0., 0.};
    vec x_c = center_mass(flock, d);
    if (x_c.x == 0 && x_c.y == 0) {
      return v3;
    }
    v3 = (x_c - get_p()) * c;
    return v3;
  }
};

class Flock {
 private:
  double mean_position_;
  double standard_d_postion_;
  double mean_velocity_;
  double standard_d_velocity_;
};

// Main
int main() {
  double frame{60};
  double delta{1 / frame};

  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_real_distribution<> dis(250., 600.);
  std::uniform_real_distribution<> dis2(-1., 1.);

  double num_boids{0.};
  double d_s{0.};
  double d{0.};
  double s{0.};
  double a{0.};
  double c{0.};
  set_parameters(num_boids, d, d_s, s, a, c);

  // flock generarion
  std::vector<Boid> flock;
  for (int i = 0; i < num_boids; ++i) {
    flock.push_back(Boid(dis(eng), dis(eng), dis2(eng), dis2(eng)));
  }
  // graphic
  sf::RenderWindow window(sf::VideoMode(900, 900), "Boids");

  // setting the framerate
  window.setFramerateLimit(frame);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear(sf::Color(135, 206, 250));
    for (auto& boid : flock) {
      // The circle rappresent a boid
      sf::CircleShape circle(1);
      boid.update_v(boid.separation(flock, s, d_s), boid.alignment(flock, a, d),
                    boid.cohesion(flock, c, d));
      boid.update_p(delta);
      boid.borders();

      // Setting the position of the circle
      circle.setPosition(boid.get_p().x, boid.get_p().y);

      circle.setFillColor(sf::Color::Black);
      window.draw(circle);
    }
    window.display();
  }
}
