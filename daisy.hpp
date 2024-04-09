#ifndef DAISY_HPP
#define DAISY_HPP

enum class DaisyColor { Black, White, None };

class Daisy {
  DaisyColor color_{DaisyColor::None};
  int age_{0};

 public:
  Daisy() = default;
  Daisy(DaisyColor color, int age) : color_{color}, age_{age} {}
};

#endif  // DAISY_HPP
