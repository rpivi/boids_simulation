#ifndef TRIANGLESFML_HPP
#define TRIANGLESFML_HPP

#include <SFML/Graphics.hpp>

namespace tr {
sf::ConvexShape createTriangle(const sf::Vector2f& position,
                               const sf::Vector2f& velocity);
}
#endif