#include <iostream>
#include <vector>

void input_vector(std::vector<int>& v) {
  int broj;
  std::cout << "Unesite brojeve (0 za kraj unosa): ";
  while(true) {
    std::cin >> broj;
    if (broj == 0) break;
    v.push_back(broj);
    }
}

void print_vector(const std::vector<int>& v) {
  std::cout << "Vektor sadrzi: ";
  for (int broj : v) {
    std::cout << broj << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::vector<int> v;

  input_vector(v);
  print_vector(v);

  return 0;
}