#include "twodimensional.hpp"

#include <cmath>

namespace two_dim {
// overloading operator
vec operator+(vec const& a, vec const& b) { return vec{a.x + b.x, a.y + b.y}; }
vec operator-(vec const& a, vec const& b) { return vec{a.x - b.x, a.y - b.y}; }
vec operator*(vec const& a, double const& b) { return vec{a.x * b, a.y * b}; }
vec operator/(vec const& a, int b) { return vec{a.x / b, a.y / b}; }

// norm and distance function
double norm(vec const& p) { return std::hypot(p.x, p.y); }


double distance(vec const& p, vec const& otherp) {
  vec difference = p - otherp;
  return norm(difference);
}
}  // namespace two_dim
