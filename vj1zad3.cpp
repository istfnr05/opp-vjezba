#include <iostream>
#include <cctype>

int main() {
  std::string s;

  std::cout << "Unesite string: " << std::endl;
  std::getline(std::cin, s);

  for (char& c : s) {
    if (std::isalpha(c)) {
      c = std::toupper(c);
    } else if (std::isdigit(c)) {
      c = '*';
    } else if (std::isspace(c)) {
      c = '_';
    }
  }
  std::cout << "\nModificirani string: " << s << std::endl;
  return 0;
}