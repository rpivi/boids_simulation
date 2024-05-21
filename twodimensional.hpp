#ifndef TWODIMENSIONAL_HPP
#define TWODIMENSIONAL_HPP

namespace two_dim {
struct vec {
  double x;
  double y;
};
// overloading operator
vec operator+(vec const& a, vec const& b);
vec operator-(vec const& a, vec const& b);
vec operator*(vec const& a, double const& b);
vec operator/(vec const& a, int b);

// norm and distance function
double norm(vec const& p);

double distance(vec const& p, vec const& otherp);

}  // namespace two_dim
#endif