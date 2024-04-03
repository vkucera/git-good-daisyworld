#ifndef DAISY_HPP
#define DAISY_HPP

#include <cmath>

enum class DaisyColor { Black, White, None };

class Daisy {
  DaisyColor color_{DaisyColor::None};
  int age_{0};
  double temperature_{0.};
  struct Albedo {
    static constexpr double black{0.25};
    static constexpr double white{0.75};
    static constexpr double surface{0.4};
  };

 public:
  Daisy() = default;
  Daisy(DaisyColor color, int age) : color_{color}, age_{age} {}

  double temperature() const {
    return temperature_;
  }
  void temperature(double t) {
    temperature_ = t;
  }

  void absorb_light(double solar_luminosity);
};

inline double local_heating(double solar_luminosity, double albedo) {
  double absorbed_luminosity{solar_luminosity * (1. - albedo)};
  return absorbed_luminosity > 0. ? 72. * std::log(absorbed_luminosity) + 80.
                                  : 80.;
}

#endif  // DAISY_HPP
