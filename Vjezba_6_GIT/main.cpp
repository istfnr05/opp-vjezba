#include <iostream>
#include "container.h"

Container napraviContainer() {
    Container c;
    c.push_back(100);
    return c;
}

void primiPoVrijednosti(Container c) {
    std::cout << "Primljen container po vrijednosti (copy ctor)\n";
}

int main() {
    std::cout << "--- 1. Kreiranje containera i dodavanje elemenata ---\n";
    Container c1(2);
    c1.push_back(10);
    c1.push_back(20);
    c1.push_back(30);

    std::cout << "--- 2. Copy konstruktor ---\n";
    Container c2 = c1;

    std::cout << "--- 3. Move konstruktor ---\n";
    Container c3 = std::move(c1);

    std::cout << "--- 4. Slanje po vrijednosti (copy) ---\n";
    primiPoVrijednosti(c2);

    std::cout << "--- 5. Vraćanje iz funkcije (move) ---\n";
    Container c4 = napraviContainer();

    std::cout << "--- 6. Realokacija dodavanjem elemenata ---\n";
    c4.push_back(1);
    c4.push_back(2);
    c4.push_back(3);
    c4.push_back(4);

    std::cout << "--- 7. Ispis elemenata ---\n";
    for (size_t i = 0; i < c4.size(); i++)
        std::cout << "index " << i << " = " << c4.at(i) << "\n";

    return 0;
}
