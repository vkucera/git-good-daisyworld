#include "daisy.hpp"

void Daisy::sprout(DaisyColor color) {
  color_ = color;
  age_ = 0;
}

void Daisy::age_and_die(int max_age) {
  if (++age_ > max_age) {
    color_ = DaisyColor::None;
  }
}

void Daisy::absorb_light(double solar_luminosity) {
  double albedo = 0.;
  switch (color_) {
    case DaisyColor::Black:
      albedo = Albedo::black;
      break;
    case DaisyColor::White:
      albedo = Albedo::white;
      break;
    case DaisyColor::None:
    default:
      albedo = Albedo::surface;
      break;
  }
  temperature_ = (temperature_ + local_heating(solar_luminosity, albedo)) * 0.5;
}