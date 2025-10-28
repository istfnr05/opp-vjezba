#include <iostream>
#include <cstddef>
#include <algorithm>

void sortt(int arr[], std::size_t size, bool (*cmp)(int, int)) {
    for (std::size_t i = 0; i < size - 1; ++i) {
        for (std::size_t j = 0; j < size - 1 - i; ++j) {
            if (!cmp(arr[j], arr[j + 1])) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

inline bool ascending(int a, int b) {
    return a <= b;
}

inline bool descending(int a, int b) {
    return a >= b;
}

void printArray(const int arr[], std::size_t size) {
    for (std::size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << (i == size - 1 ? "" : ", ");
    }
    std::cout << std::endl;
}

int main() {
    int data[] = {5, 2, 9, 1, 5, 6};
    const std::size_t size = sizeof(data) / sizeof(data[0]);

    std::cout << "Originalni niz: ";
    printArray(data, size);

    sortt(data, size, ascending);

    std::cout << "Niz nakon UZLAZNOG sortiranja: ";
    printArray(data, size);

    int data2[] = {5, 2, 9, 1, 5, 6};

    sortt(data2, size, descending);

    std::cout << "Niz nakon SILAZNOG sortiranja: