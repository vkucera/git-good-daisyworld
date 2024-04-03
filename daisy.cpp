#include "daisy.hpp"

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