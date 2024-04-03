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

void World::compute_temperatures(double solar_luminosity) {
  for (auto &daisy : daisies_) {
    daisy.absorb_light(solar_luminosity);
  }
}

double World::global_temperature() const {
  return std::accumulate(daisies_.begin(), daisies_.end(), 0.,
                         [](double sum, Daisy const &daisy) {
                           return sum + daisy.temperature();
                         }) /
         daisies_.size();
}

void World::step(double solar_luminosity) {
  compute_temperatures(solar_luminosity);
  compute_diffusion();
  spread();
}

std::vector<double> diffuse(std::vector<double> const &temperatures, int size,
                            double diffusion_rate) {
  std::vector<double> new_temperatures(size * size);
  for (int idx{0}; idx < size * size; ++idx) {
    double temperature = temperatures[idx];
    double const diffused_temperature = temperature * diffusion_rate / 8;
    int const row = idx / size;
    int const col = idx % size;
    for (int neighborRow : {row - 1, row, row + 1}) {
      for (int neighborCol : {col - 1, col, col + 1}) {
        // Check if the neighbor is within the grid bounds
        if (neighborRow >= 0 && neighborRow < size && neighborCol >= 0 &&
            neighborCol < size) {
          new_temperatures[neighborRow * size + neighborCol] +=
              diffused_temperature;
          temperature -= diffused_temperature;
        }
      }
    }
    // Keep leftover temperature
    new_temperatures[idx] += temperature;
  }
  // Update original patches
  return new_temperatures;
}

void World::compute_diffusion() {
  std::vector<double> temperatures;
  temperatures.reserve(daisies_.size());
  for (auto const &p : daisies_) {
    temperatures.push_back(p.temperature());
  }

  auto new_temperatures = diffuse(temperatures, size_, 0.5);

  for (int i{0}; i < size_ * size_; ++i) {
    daisies_[i].temperature(new_temperatures[i]);
  }
}

void World::spread() {
  for (auto &daisy : daisies_) {
    daisy.age_and_die(max_age_);
  }
  auto new_daisies = daisies_;

  std::uniform_real_distribution<double> flat;
  for (int idx{0}; idx < size_ * size_; ++idx) {
    auto &daisy = daisies_[idx];
    if (daisy.color() == DaisyColor::None ||
        flat(gen_) >= daisy.seeding_threshold()) {
      continue;
    }
    std::vector<Daisy *> barren_neighbors;
    int const row = idx / size_;
    int const col = idx % size_;
    for (int neighborRow : {row - 1, row, row + 1}) {
      for (int neighborCol : {col - 1, col, col + 1}) {
        if (neighborRow >= 0 && neighborRow < size_ && neighborCol >= 0 &&
            neighborCol < size_) {
          auto &neighbor = new_daisies[neighborRow * size_ + neighborCol];
          if (neighbor.color() == DaisyColor::None) {
            barren_neighbors.emplace_back(&neighbor);
          }
        }
      }
    }
    if (barren_neighbors.size() > 0) {
      std::uniform_int_distribution<> flat_i(0, barren_neighbors.size() - 1);
      barren_neighbors[flat_i(gen_)]->sprout(daisy.color());
    }
  }
  daisies_ = new_daisies;
}

void World::print() {
  for (int i{0}; i < size_; ++i) {
    for (int j{0}; j < size_; ++j) {
      std::cout << daisies_[i * size_ + j];
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}
