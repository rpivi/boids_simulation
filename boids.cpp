#include <cassert>
#include <cmath>
#include <vector>

struct two_d {
  double x;
  double y;
};

two_d operator+(two_d const& a, two_d const& b) {
  return two_d{a.x + b.x, a.y + b.y};
}
two_d operator*(two_d const& a, auto const& b) {
  return two_d{a.x * b, a.y * b};
}

class Boid {
 private:
  two_d position_;
  two_d velocity_;

 public:
  Boid(two_d p, two_d v) : position_{p}, velocity_{v} {}

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
    // delta_t deve essere positivo
    position_ = position_ + velocity_ * delta_t;
  }
};

int main() {

std::vector<Boid> flock;



}
