#include <cassert>
#include <cmath>
#include <vector>

struct two_d {
  double x;
  double y;
};

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
    // overload dell'operatore + da fare per 2d
  }
  two_d update_p(double delta_t) {
    assert(delta_t > 0);
    // delta_t deve essere positivo
    position_ = position_ + velocity_ * delta_t;
    // overload dell'operatore * da fare per 2d (in caso si moltiplichi per una
    // costante)
  }
};

class Flock {
 private:
  std::vector<Boid> formation_;

 public:
  Flock() {}  // costruttore e classe da implementare
};

two_d separation(double s, double radius) {
  // da implementare, restituisce v1
}

two_d allineament(double a) {
  // da implementare, restituisce v2
}

two_d cohesion(double c) {
  // da implementare, restituisce v3
}

int main() {}
