#include <iostream>
#include <cmath>

int& at(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return arr[0];
}


int main() {
    const int N = 5;
    int numbers[N] = {10, 20, 30, 40, 50};
    int target_index = 2;

    std::cout << "Originalni niz:" << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;
    }

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Ciljani element: numbers[" << target_index << "] = " << numbers[target_index] << std::endl;

    at(numbers, N, target_index) += 1;

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Nakon uvecanja:" << std::endl;

    std::cout << "numbers[" << target_index << "] je sada: " << numbers[target_index] << std::endl;

    std::cout << "\nNovi cijeli niz:" << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;
    }

    return 0;
}