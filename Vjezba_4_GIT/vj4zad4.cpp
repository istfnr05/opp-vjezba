#include <iostream>
#include <string>

std::string word_to_pig_latin(const std::string& word){
  std::string samoglasnici = "aeiouAEIOU";

  if (samoglasnici.find(word[0]) != std::string::npos) {
    return word + "hay";
  } else {
    return word.substr(1) + word[0] + "ay";
  }
}

int main() {
  std::string w1 = "apple";
  std::string w2 = "hello";

  std::cout << w1 << "->" << word_to_pig_latin(w1) << std::endl;
  std::cout << w2 << "->" << w1 << std::endl;

  return 0;
}