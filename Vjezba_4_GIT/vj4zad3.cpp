#include <iostream>
#include <string>
#include <cctype>

void fix_space(std::string& text) {
  for (size_t i = 1; i < text.size(); ) {
    if (isspace(text[i]) && isspace(text[i - 1])) {
      text.erase(i, 1);
    } else {
      i++;
    }
  }

  for (size_t i = 0; i < text.size(); i++) {
    if (text[i] == ',' || text[i] == '.') {
      if (i > 0 && isspace(text[i - 1])) {
        text.erase(i - 1, 1);
        i--;
      }

      if (text[i] == ',' && (i + 1 < text.size()) && !isspace(text[i + 1])) {
        text.insert(i + 1, " ");
        i++;
      }
    }
  }
}

int main() {
  std::string text = "Puno razmaka ,i tocka .";
  std::cout << "Prije: \"" << text << "\"";

  fix_space(text);

  std::cout << "Poslije: \"" << text << "\"";
  return 0;
}