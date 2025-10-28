#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include <string>

void printVector(const std::vector<int>& vec, const std::string& name) {
    std::cout << name << ": [";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << (i == vec.size() - 1 ? "" : ", ");
    }
    std::cout << "]" << std::endl;
}

auto is_even = [](int n) -> bool { return n % 2 == 0; };
auto is_odd = [](int n) -> bool { return n % 2 != 0; };

auto double_it = [](int n) -> int { return n * 2; };
auto half_it = [](int n) -> int { return n / 2; };

auto add_to_sum_ref = [](int n, long long& sum) { sum += n; };
auto add_to_product_ref = [](int n, long long& product) { product *= n; };

auto add_if_above_threshold = [](int threshold, long long& sum)
    -> std::function<void(int)>
{
    return [threshold, &sum](int n) {
        if (n > threshold) {
            sum += n;
        }
    };
};

void transform_array(std::vector<int>& arr) {
    std::cout << "\n--- 1. Transformacija niza ---" << std::endl;
    for (int& element : arr) {
        if (is_even(element)) {
            element = half_it(element);
        } else {
            element = double_it(element);
        }
    }
}

void calculate_sum_and_product(const std::vector<int>& arr) {
    long long sum = 0;
    long long product = 1;

    auto sum_lambda = [&](int n) { add_to_sum_ref(n, sum); };
    auto product_lambda = [&](int n) { add_to_product_ref(n, product); };

    for (int n : arr) {
        sum_lambda(n);
        product_lambda(n);
    }

    std::cout << "\n--- 2. Suma i Produkt niza ---" << std::endl;
    std::cout << "Suma: " << sum << std::endl;
    std::cout << "Produkt: " << product << std::endl;
}

long long calculate_sum_above_threshold(const std::vector<int>& arr, int threshold) {
    long long sum_above = 0;

    auto check_and_add = add_if_above_threshold(threshold, sum_above);

    for (int n : arr) {
        check_and_add(n);
    }

    return sum_above;
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> numbers_copy = numbers;
    
    printVector(numbers, "Inicijalni niz");

    transform_array(numbers);
    printVector(numbers, "Transformirani niz");

    calculate_sum_and_product(numbers_copy);

    int threshold_value = 7;
    long long sum_result = calculate_sum_above_threshold(numbers_copy, threshold_value);
    
    std::cout << "\n--- 3. Suma iznad praga ---" << std::endl;
    std::cout << "Prag (threshold): " << threshold_value << std::endl;
    std::cout << "Suma brojeva vecih od " << threshold_value << ": " << sum_result << std::endl;

    return 0;
}