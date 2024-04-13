#include <cassert>
#include <cmath>
#include <random>
#include <vector>

// random generation of number
///////////////////////////////////////////////////////////////////////////////////////////
std::default_random_engine eng;
std::uniform_int_distribution<> roll_dice(1, 100);

// two dimensional rappresewntation
////////////////////////////////////////////////////////////////////////////////////////////
struct two_d {
  double x;
  double y;
};

// overloading operator
two_d operator+(two_d const& a, two_d const& b) {
  return two_d{a.x + b.x, a.y + b.y};
}
two_d operator*(two_d const& a, auto const& b) {
  return two_d{a.x * b, a.y * b};
}

// Boid
// //////////////////////////////////////////////////////////////////////////////////////////
class Boid {
 private:
  two_d position_;
  two_d velocity_;

 public:
  Boid()  // random number by default
      : position_{roll_dice(eng), roll_dice(eng)},
        velocity_{roll_dice(eng), roll_dice(eng)} {}

  two_d p() const { return position_; }
  two_d v() const { return velocity_; }

  bool near(Boid const& other, double radius) const {
    if (std::sqrt(pow(position_.x - other.position_.x, 2)) +
            pow(position_.y - other.position_.y, 2) <=
        radius) {
      return true;
    }
  }
  two_d update_v(two_d const& v1, two_d const& v2, two_d const& v3) {
    velocity_ = velocity_ + v1 + v2 + v3;
  }

  two_d update_p(double delta_t) {
    assert(delta_t > 0);
    position_ = position_ + velocity_ * delta_t;
  }
};

// Main
/////////////////////////////////////////////////////////////////////////////////////////////
int main() {
  int num_boids;
  std::vector<Boid> flock;

  for (int i = 0; i < num_boids; ++i) {
    flock.push_back(Boid());
  }
}
