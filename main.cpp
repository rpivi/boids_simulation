#include <SFML/Graphics.hpp>
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>

#include "birds.hpp"

sf::ConvexShape createTriangle(const sf::Vector2f& position, const sf::Vector2f& velocity) {
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0, -5)); // Top point
    triangle.setPoint(1, sf::Vector2f(-3, 3)); // Bottom left point
    triangle.setPoint(2, sf::Vector2f(3, 3));  // Bottom right point

    // Calculate the angle of rotation based on the velocity
    float angle = std::atan2(velocity.y, velocity.x) * static_cast<float>(180. / 3.141592);
    triangle.setRotation(angle + 90); // Rotate by 90 degrees to align the point upwards

    triangle.setPosition(position);
    triangle.setFillColor(sf::Color::Black);

    return triangle;
}


// Main
int main() {
  double frame{60};
  double delta{1 / frame};

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
    //clear the window - background color blue as the sky
    window.clear(sf::Color(135, 206, 250));

    //boids out of the windows must come back - toroidal space
    for(auto& boid: flock){
      boid.borders();
    }

    //updating the flock 
    for (auto& boid : flock) {
      boid.update_v(boid.separation(flock, s, d_s), boid.alignment(flock, a, d),
                    boid.cohesion(flock, c, d));
      boid.update_p(delta);

      //the boids are a black triangle
      sf::ConvexShape triangle = createTriangle(sf::Vector2f(static_cast<float>(boid.get_p().x),static_cast<float>(boid.get_p().y)),
                                                  sf::Vector2f(static_cast<float>(boid.get_v().x), static_cast<float>(boid.get_v().y)));

      window.draw(triangle);
    }
    window.display();

    birds::Flock Flock_Statistics;
    Flock_Statistics.mean_position(flock);
    Flock_Statistics.mean_velocity(flock);
    Flock_Statistics.std_dev_p(flock);
    Flock_Statistics.std_dev_v(flock);

    std::cout << Flock_Statistics.get_mean_p().x << "\t\t  "
              << Flock_Statistics.get_mean_p().y << "\t   "
              << Flock_Statistics.get_std_dev_p().x << "\t   "
              << Flock_Statistics.get_std_dev_p().y << "\t   "
              << Flock_Statistics.get_mean_v().x << "\t    "
              << Flock_Statistics.get_mean_v().y << "\t     "
              << Flock_Statistics.get_std_dev_v().x << "\t     "
              << Flock_Statistics.get_std_dev_v().y << "\n";
  }
}