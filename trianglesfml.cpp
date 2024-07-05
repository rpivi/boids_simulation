#include "trianglesfml.hpp"

#include <cmath>

namespace tr {


sf::ConvexShape createTriangle(const sf::Vector2f& position,
                               const sf::Vector2f& velocity) {
  sf::ConvexShape triangle;
  triangle.setPointCount(3);
  triangle.setPoint(0, sf::Vector2f(0, -5));  // Top point
  triangle.setPoint(1, sf::Vector2f(-3, 3));  // Bottom left point
  triangle.setPoint(2, sf::Vector2f(3, 3));   // Bottom right point

  // Calculate the angle of rotation based on the velocity
  float angle =
      std::atan2(velocity.y, velocity.x) * static_cast<float>(180. / 3.141593);
  triangle.setRotation(angle +
                       90);  // Rotate by 90 degrees to align the point upwards

  triangle.setPosition(position);
  triangle.setFillColor(sf::Color::Black);

  return triangle;
}

}  // namespace tr
