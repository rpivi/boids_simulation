#include <SFML/Graphics.hpp>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>

// constant value
///////////////////////////////////////////////////////////////////////////////////////////
const int num_boids{500};
const double radius{25};
const double s{0.5};
const double a{1.};
const double c{0.5};
const double frame{30};
const double delta{1.};

// random generation of number
///////////////////////////////////////////////////////////////////////////////////////////
std::default_random_engine eng;
std::uniform_real_distribution<> dis(100., 800.0);
std::uniform_real_distribution<> dis2(-1., 1.);

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
    if (std::sqrt(pow(position_.x - other.position_.x, 2)) +
            pow(position_.y - other.position_.y, 2) <=
        radius) {
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
};

// center of mass
////////////////////////////////////////////////////////////////////////////////////////////
two_d center_mass(std::vector<Boid> const& flock, Boid bird) {
  two_d x_c{0., 0.};
  int n{0};
  for (auto& other_b : flock) {
    if (bird.get_p().x != other_b.get_p().x &&
        bird.get_p().y != other_b.get_p().y) {
      if (bird.near(other_b, radius)) {
        ++n;
        x_c = x_c + other_b.get_p();
      }
    }
  }
  if (n != 1) {
    return x_c * (1 / (n - 1));
  } else {
    return {0., 0.};
  }
}

// 3 laws
/////////////////////////////////////////////////////////////////////////////////////////////
two_d separation(Boid const& bird, std::vector<Boid> const& flock,
                 double const& s) {
  two_d v1{0., 0.};
  for (auto& other_b : flock) {
    if (bird.near(other_b, radius)) {
      v1 = (other_b.get_p() - bird.get_p()) + v1;
    }
  }
  return v1 * (-s);
}
two_d alignment(Boid const& bird, std::vector<Boid> const& flock,
                double const& a) {
  two_d v2{0., 0.};
  int n{0};
  for (auto& other_b : flock) {
    if (bird.near(other_b, radius)) {
      ++n;
      v2 = (other_b.get_v() - bird.get_v()) + v2;
    }
  }
  if (n != 1) {
    return v2 * (a / (n - 1));
  } else {
    return {0., 0.};
  }
}

two_d cohesion(Boid const& bird, std::vector<Boid> const& flock,
               double const& c) {
  two_d v3{0., 0.};
  two_d x_c = center_mass(flock, bird);
  if (x_c.x == 0 && x_c.y == 0) {
    return v3;
  }

  v3 = (x_c - bird.get_p()) * c;
  return v3;
}
// Main
/////////////////////////////////////////////////////////////////////////////////////////////
int main() {
  std::vector<Boid> flock;

  for (int i = 0; i < num_boids; ++i) {
    flock.push_back(Boid());
  }

  // graphics
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  sf::RenderWindow window(sf::VideoMode(900, 900), "Boids");
  window.setFramerateLimit(frame);
  // framerate per non avere un video troppo veloce

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear();

    for (auto& boid : flock) {
      // Creazione del cerchio per rappresentare un boid
      sf::CircleShape circle(2);
      boid.update_v(separation(boid, flock, s), alignment(boid, flock, a),
                    cohesion(boid, flock, c));
      boid.update_p(delta);

      // Impostazione della posizione del cerchio sulle coordinate del boid
      circle.setPosition(boid.get_p().x, boid.get_p().y);

      // Impostazione del colore del cerchio
      circle.setFillColor(sf::Color::Blue);
      window.draw(circle);
    }
    window.display();
  }
}
