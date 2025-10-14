#include <iostream>
#include <iomanip>

int clamp_value(int value, int min = 0, int max = 100) {
  if (value < min) {
    return min;
  }
  if (value > max) {
    return max;
  }
  return value;
}
double clamp_value(double value, double min = 0.0, double max = 1.0) {
  if (value < min) {
    return min;
  }
  if (value > max) {
    return max;
  }
  return value;
}

int main() {
  std::cout << " --- Testiranje int funkcije (int clamp_value) --- " << std::endl;

  int res1 = clamp_value(-15);
  std::cout << "clamp_value(-15) -> " << res1 << std::endl;
  int res2 = clamp_value(50);
  std::cout << "clamp_value(50) -> " << res2 << std::endl;

  std::cout << " --- Testiranje double funkcije (double clamp_value) --- " << std::endl;
  std::cout << std::fixed << std::setprecision(4);

  double res3 = clamp_value(-2.0);
  std::cout << "clamp_value(-2.0) -> " << res3 << std::endl;

  double res4 = clamp_value(3.0);
  std::cout << "clamp_value(3.0) -> " << res4 << std::endl;

  return 0;
}