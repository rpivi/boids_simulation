#include <SFML/Graphics.hpp>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>

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
        velocity_{roll_dice(eng), roll_dice(eng)} {}

  two_d p() const { return position_; }
  two_d v() const { return velocity_; }

  bool near(Boid const& other, double radius) {
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

// le 3 leggi
/////////////////////////////////////////////////////////////////////////////////////////////

// Main
/////////////////////////////////////////////////////////////////////////////////////////////
int main() {
  double radius{50};
  int num_boids{500};
  std::vector<Boid> flock;
  bool info_near[num_boids][num_boids];

  for (int i = 0; i <= num_boids; ++i) {
    flock.push_back(Boid());
  }
  for (int row = 0; row < num_boids; ++row)
    for (int col = 0; col < num_boids; ++col) {
      if (flock[row].near(flock[col], radius)) {
        info_near[row][col] = true;
      } else
        (info_near[row][col] = false);
      std::cout << info_near[row][col];
    }

  sf::RenderWindow window(sf::VideoMode(900, 900), "Boids");
  window.setFramerateLimit(30);
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

      // Impostazione della posizione del cerchio sulle coordinate del boid
      circle.setPosition(boid.p().x, boid.p().y);

      // Impostazione del colore del cerchio
      circle.setFillColor(sf::Color::Blue);
      window.draw(circle);
    }

    window.display();
  }
}
