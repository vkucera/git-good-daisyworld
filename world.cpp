#include "world.hpp"

#include <algorithm>
#include <random>

World::World(int size, double start_black_percentage,
             double start_white_percentage, int max_age)
    : size_{size}, max_age_{max_age} {
  auto const num_daisies_ = size_ * size_;
  daisies_.reserve(num_daisies_);

  auto const num_black_patches =
      static_cast<int>(num_daisies_ * start_black_percentage);
  auto const num_white_patches =
      static_cast<int>(num_daisies_ * start_white_percentage);
  auto const num_empty_patches =
      num_daisies_ - num_black_patches - num_white_patches;

  std::uniform_int_distribution<int> dist{0, max_age_};

  // Generate daisies with random colors and ages using generators
  auto out =
      std::generate_n(std::back_inserter(daisies_), num_black_patches, [&] {
        return Daisy{DaisyColor::Black, dist(gen_)};
      });
  out = std::generate_n(out, num_white_patches, [&] {
    return Daisy{DaisyColor::White, dist(gen_)};
  });
  std::generate_n(out, num_empty_patches, [] {
    return Daisy{DaisyColor::None, 0};
  });

  // Shuffle the daisies
  std::shuffle(daisies_.begin(), daisies_.end(), gen_);
}
