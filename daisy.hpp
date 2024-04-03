#ifndef DAISY_HPP
#define DAISY_HPP

#include <cmath>
#include <iostream>

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

  DaisyColor color() const {
    return color_;
  }

  double seeding_threshold() {
    return ((0.1457 * temperature_) - (0.0032 * (temperature_ * temperature_)) -
            0.6443);
  }

  void sprout(DaisyColor color);

  void age_and_die(int max_age);

  void absorb_light(double solar_luminosity);
  friend std::ostream& operator<<(std::ostream& os, const Daisy& daisy);
};

inline double local_heating(double solar_luminosity, double albedo) {
  double absorbed_luminosity{solar_luminosity * (1. - albedo)};
  return absorbed_luminosity > 0. ? 72. * std::log(absorbed_luminosity) + 80.
                                  : 80.;
}

#endif  // DAISY_HPP

