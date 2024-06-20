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

  // graphic
  sf::RenderWindow window(sf::VideoMode(900, 900), "Boids");

  // setting the framerate
  window.setFramerateLimit(static_cast<unsigned int>(frame));

  std::cout << "Mean Position X \t Mean Position Y   "
            << "\t Standard Dev X \t Standard Dev Y \t "
            << "Mean Velocity X \t Mean Velocity Y \t "
            << "Standard Dev X \t Standard Dev Y \n";

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

    birds::Flock Flock_Statistics;
    Flock_Statistics.mean_position(flock);
    Flock_Statistics.mean_velocity(flock);
    Flock_Statistics.std_dev_p(flock);
    Flock_Statistics.std_dev_v(flock);

    std::cout << Flock_Statistics.get_mean_p().x << "\t"
              << Flock_Statistics.get_mean_p().y << "\t"
              << Flock_Statistics.get_std_dev_p().x << "\t"
              << Flock_Statistics.get_std_dev_p().y << "\t"
              << Flock_Statistics.get_mean_v().x << "\t"
              << Flock_Statistics.get_mean_v().y << "\t"
              << Flock_Statistics.get_std_dev_v().x << "\t"
              << Flock_Statistics.get_std_dev_v().y << "\n";
  }
}
