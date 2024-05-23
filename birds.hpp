#ifndef BIRDS_HPP
#define BIRDS_HPP

#include "twodimensional.hpp"
#include <vector>

namespace birds{
    // get parameters
///////////////////////////////////////////////////////////////////////////////////////////

void set_parameters(double& num_boids, double& d, double& d_s, double& s,
                    double& a, double& c);

// Boid
/////////////////////////////////////////////////////////////////////////////////////////////
class Boid {
 private:
  two_dim::vec position_;
  two_dim::vec velocity_;

 public:
  // Constructor
  Boid(double posX, double posY, double velX, double velY);

  two_dim::vec get_p() const { return position_; }
  two_dim::vec get_v() const { return velocity_; }

  // near function
  bool near(Boid const& other, double d) const;
  void update_v(two_dim::vec const& v1, two_dim::vec const& v2, two_dim::vec const& v3);

  void update_p(double delta_t);

  // toroidal space
  void borders();

  // center of mass
  two_dim::vec center_mass(std::vector<Boid> const& flock, double const& d);

  // 3 laws
  two_dim::vec separation(std::vector<Boid> const& flock, double const& s,
                   double const& d_separation);

  two_dim::vec alignment(std::vector<Boid> const& flock, double const& a,
                  double const& d);

  two_dim::vec cohesion(std::vector<Boid> const& flock, double const& c,
                 double const& d);
};

class Flock {
 private:
  double mean_position_;
  double standard_d_postion_;
  double mean_velocity_;
  double standard_d_velocity_;
};

}

#endif
