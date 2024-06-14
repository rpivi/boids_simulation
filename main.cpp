#include <SFML/Graphics.hpp>
#include <cassert>
#include <cmath>
#include <iostream>
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
    flock.push_back(birds::Boid(dis(eng), dis(eng), dis2(eng), dis2(eng)));
  }

  birds::Flock Flock_Class;
  Flock_Class.mean_position(flock);
  Flock_Class.mean_velocity(flock);
  Flock_Class.std_dev_p(flock);
  Flock_Class.std_dev_v(flock);

  // graphic
  sf::RenderWindow window(sf::VideoMode(900, 900), "Boids");

  // setting the framerate
  window.setFramerateLimit(static_cast<unsigned int>(frame));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear(sf::Color(135, 206, 250));
    for (auto& boid : flock) {
      // The circle rappresents a boid
      sf::CircleShape circle(1);
      boid.update_v(boid.separation(flock, s, d_s), boid.alignment(flock, a, d),
                    boid.cohesion(flock, c, d));
      boid.update_p(delta);
      boid.borders();

      // Setting the position of the circle
      circle.setPosition(static_cast<float>(boid.get_p().x),
                         static_cast<float>(boid.get_p().y));

      circle.setFillColor(sf::Color::Black);
      window.draw(circle);
    }
    window.display();

    std::cout << "Coordinates of the Mean Position of the flock: "
              << Flock_Class.get_mean_p().x << ", "
              << Flock_Class.get_mean_p().y << '\n';
    std::cout << "Standard Deviations associated to the Coordinates of the "
                 "Mean Position: "
              << Flock_Class.get_std_dev_p().x << ", "
              << Flock_Class.get_std_dev_p().y << '\n';
    std::cout << "Coordinates of the Mean Velocity of the flock: "
              << Flock_Class.get_mean_v().x << ", "
              << Flock_Class.get_mean_v().y << '\n';
    std::cout << "Standard Deviations associated to the Coordinates of the "
                 "Mean Velocity: "
              << Flock_Class.get_std_dev_v().x << ", "
              << Flock_Class.get_std_dev_v().y << '\n';
  }
}
