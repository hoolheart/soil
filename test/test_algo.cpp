#include <iostream>
#include <string>

#include <vector>
#include <list>
#include <unordered_map>
#include <optional>

#include <numeric>
#include <algorithm>
#include <memory>

void test_accumulate_map() {
    std::unordered_map<std::string, std::vector<double>> values{
        {"freq", {0.1, 0.2, 7.88, 9.0, -1.5}},
        {"amp", {0.5, 0.6, -0.9, -9.0, -7.15}},
        {"phase", {5.9, 16.0, -7.88, 0.1, -0.79}},
        {"real", {0.19, 20.2, 17.88, 89.0, -16.5}}};
    std::unordered_map<std::string, double> point;
    for (auto it = values.begin(); it != values.end(); ++it) {
        point[it->first] = it->second[0];
    }
    for (auto [k, v] : point) {
        std::cout << k << ": " << v << std::endl;
    }
}

int main() {
    test_accumulate_map();

    return 0;
}
