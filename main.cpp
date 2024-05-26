#include <SFML/Graphics.hpp>
#include <cassert>
#include <cmath>
#include <random>
#include "birds.hpp"

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
  birds::set_parameters(num_boids, d, d_s, s, a, c);

  // flock generarion
  std::vector<birds::Boid> flock;
  for (int i = 0; i < num_boids; ++i) {
    flock.push_back( birds::Boid(dis(eng), dis(eng), dis2(eng), dis2(eng)));
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
