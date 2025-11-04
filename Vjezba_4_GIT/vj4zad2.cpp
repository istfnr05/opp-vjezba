#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void input_vector(std::vector<int>& v) {
  int broj;
  std::cout << "Unesite elemente, 0 za prekid";
  while (true) {
    std::cin >> broj;
    if (broj == 0) break;
    v.push_back(broj);
  }
}

void print_vector(std::vector<int>& v) {
  for (int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";

  }
  std::cout << std::endl;
}

int main() {
  std::vector<int> v;
  input_vector(v);

  std::cout << "Originalni vektor";
  print_vector(v);

  std::vector<int> jedinstveni;
  for (int broj : v) {
    if (std::find(jedinstveni.begin(), jedinstveni.end(), broj) == jedinstveni.end()) {
      jedinstveni.push_back(broj);
    }
  }

  std::cout << "Jedinstveni elem.: ";
  print_vector(jedinstveni);

  std::sort(jedinstveni.begin(), jedinstveni.end(),
    [](int a, int b) {return abs(a) < abs(b);});

  std::cout << "Sortirani po abs. vrijednosti: ";
  print_vector(jedinstveni);

  return 0;
}

