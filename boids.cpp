#include <SFML/Graphics.hpp>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>

// constant value
///////////////////////////////////////////////////////////////////////////////////////////
const int num_boids{500};
const double radius{50};
const double s{0.999999};
const double delta{1};
const double frame{60};

// random generation of number
///////////////////////////////////////////////////////////////////////////////////////////
std::default_random_engine eng;
std::uniform_int_distribution<> roll_dice(100, 800);

// two dimensional rappresentation
////////////////////////////////////////////////////////////////////////////////////////////
struct two_d {
  int x;
  int y;
};

// overloading operator
two_d operator+(two_d const& a, two_d const& b) {
  return two_d{a.x + b.x, a.y + b.y};
}
two_d operator*(two_d const& a, int const& b) {
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
      : position_{roll_dice(eng), roll_dice(eng)},
        velocity_{roll_dice(eng) * (roll_dice(eng) % 2 == 0 ? 1 : -1) / 400,
                  roll_dice(eng) * (roll_dice(eng) % 2 == 0 ? 1 : -1) / 400} {}

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
// 3 laws
/////////////////////////////////////////////////////////////////////////////////////////////
two_d separation(Boid const& bird, std::vector<Boid> const& flock,
                 double const& s) {
  two_d v1{0, 0};
  for (auto& b : flock) {
    if (bird.near(b, radius)) {
      v1.x = (bird.get_p().x - b.get_p().x) + v1.x;
      v1.y = (bird.get_p().y - b.get_p().y) + v1.y;
    }
  }
  return v1 * (-s);
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

      boid.update_v(separation(boid, flock, s), {0, 0}, {0, 0});
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
