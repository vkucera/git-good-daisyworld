#include "world.hpp"

#include <iostream>

int main() {
  int size{20};
  double start_black_percentage{0.2};
  double start_white_percentage{0.2};
  int max_age{25};
  World world(size, start_black_percentage, start_white_percentage, max_age);
  std::cout << "Initial global temperature: " << world.global_temperature()
            << '\n';
  world.print();

  std::cin.get();
  std::cout << "\033c"; // Clear the terminal

  world.step(1.);
  std::cout << "Global temperature after one time step: "
            << world.global_temperature() << '\n';
  world.print();
  return 0;
}
