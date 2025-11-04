#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void reverse_strings(std::vector<std::string>& words) {
  for (std::string& word : words) {
    std::reverse(word.begin(), word.end());
  }
}

void print_string(const std::vector<std::string>& words) {
  std::cout << "[";
  for (size_t i = 0; i < words.size(); i++) {
    std::cout << "\"" << words[i] << "\"";
    if (i < words.size() - 1) std::cout << ",";
  }
  std::cout << "]" << std::endl;
}

int main() {
  std::vector<std::string> words = {"hello", "world", "c++"};
  reverse_strings(words);
  print_string(words);
  return 0;
}