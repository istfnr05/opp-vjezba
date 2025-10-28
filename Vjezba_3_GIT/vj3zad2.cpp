#include <iostream>
#include <cstddef>
#include <algorithm>
#include <string>
#include <type_traits> // Za std::is_floating_point_v

template <typename T>
void sort(T arr[], std::size_t size, bool (*cmp)(T, T)) {
    for (std::size_t i = 0; i < size - 1; ++i) {
        for (std::size_t j = 0; j < size - 1 - i; ++j) {
            if (!cmp(arr[j], arr[j + 1])) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template <typename T>
inline bool ascending(T a, T b) {
    return a <= b;
}

template <typename T>
inline bool descending(T a, T b) {
    return a >= b;
}

template <typename T>
void printArray(const T arr[], std::size_t size, const std::string& type) {
    std::cout << type << " niz: [";
    for (std::size_t i = 0; i < size; ++i) {
        if constexpr (std::is_floating_point_v<T>) {
            std::cout.precision(2);
            std::cout << std::fixed;
        }
        std::cout << arr[i] << (i == size - 1 ? "" : ", ");
    }
    std::cout << "]" << std::endl;
}

int main() {
    int int_data[] = {5, 2, 9, 1, 5, 6};
    const std::size_t int_size = sizeof(int_data) / sizeof(int_data[0]);

    std::cout << "--- TESTIRANJE ZA INT NIZ ---" << std::endl;
    printArray(int_data, int_size, "Originalni INT");

    sort(int_data, int_size, ascending<int>);
    printArray(int_data, int_size, "INT UZLAZNO");
    
    double double_data[] = {3.14, -1.5, 9.99, 0.0, 4.2};
    const std::size_t double_size = sizeof(double_data) / sizeof(double_data[0]);

    std::cout << "\n--- TESTIRANJE ZA DOUBLE NIZ ---" << std::endl;
    printArray(double_data, double_size, "Originalni DOUBLE");

    sort(double_data, double_size, descending<double>);
    printArray(double_data, double_size, "DOUBLE SILAZNO");

    return 0;
}