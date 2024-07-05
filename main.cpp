#include <cassert>
#include <cmath>
#include <iostream>
#include <random>

#include "birds.hpp"
#include "trianglesfml.hpp"

// Main
int main() {
  double frame{60};
  double delta{1 / frame};


  // random generation
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_real_distribution<> dis(400., 500.);
  std::uniform_real_distribution<> dis2(-3., 3.);

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

  // the window
  sf::RenderWindow window(sf::VideoMode(900, 900), "Boids");

  // setting the framerate
  window.setFramerateLimit(static_cast<unsigned int>(frame));

  // the output in the terminal and in the window
  std::cout << "Mean Position X   Mean Position Y  "
            << "Standard Dev X  Standard Dev Y  "
            << "Mean Velocity X  Mean Velocity Y  "
            << "Standard Dev X  Standard Dev Y \n";

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    // clear the window - background color blue as the sky
    window.clear(sf::Color(135, 206, 250));

    for (auto& boid : flock) {
      // boids out of the window must come back - toroidal space
      boid.borders();

      // updating the flock
      boid.update_v(boid.separation(flock, s, d_s), boid.alignment(flock, a, d),
                    boid.cohesion(flock, c, d));
      boid.update_p(delta);

      // the boids are a black triangle
      sf::ConvexShape triangle =
          tr::createTriangle(sf::Vector2f(static_cast<float>(boid.get_p().x),
                                          static_cast<float>(boid.get_p().y)),
                             sf::Vector2f(static_cast<float>(boid.get_v().x),
                                          static_cast<float>(boid.get_v().y)));

      window.draw(triangle);
    }
    window.display();

    birds::Flock Flock_Statistics;

    std::cout << Flock_Statistics.mean_position(flock).x << "\t\t  "
              << Flock_Statistics.mean_position(flock).y << "\t   "
              << Flock_Statistics.std_dev_p(flock).x << "\t   "
              << Flock_Statistics.std_dev_p(flock).y << "\t   "
              << Flock_Statistics.mean_velocity(flock).x << "\t    "
              << Flock_Statistics.mean_velocity(flock).y << "\t     "
              << Flock_Statistics.std_dev_v(flock).x << "\t     "
              << Flock_Statistics.std_dev_v(flock).y << "\n";
  }
}