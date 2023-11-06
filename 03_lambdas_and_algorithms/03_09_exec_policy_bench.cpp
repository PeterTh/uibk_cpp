// g++ main.cpp -O3 -std=c++20 -ltbb -Wall -Wextra -o main

#include <algorithm>
#include <iomanip>
#include <numeric>
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <execution>

constexpr int REPS = 10;
using bench_type = double;

template <typename E>
void test_exec_policy(bool dry, std::string name, E exec, std::vector<bench_type>& a, std::vector<bench_type>& b) {
    using namespace std::chrono_literals;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < REPS; ++i) {
        std::transform(exec, a.cbegin(), a.cend(), b.begin(), [](double x) { return x / (x + std::sin(x)); });
        std::transform(exec, b.cbegin(), b.cend(), a.begin(), [](double x) { return x * (x + std::cos(x)); });
    }
    auto end = std::chrono::high_resolution_clock::now();
    double elapsed = (end - start) / 1.0ms;
    if (!dry) {
        std::cout << std::setw(24) << name << " : " << std::fixed << std::setprecision(2) << std::setw(10) 
                  << elapsed / (REPS*2) << " ms\n";
    }
    else {
        std::cout << "." << std::flush;
    }
}

int main(int argc, char** argv) {

    size_t n = 10000000;
    if(argc>1) n = std::atol(argv[1]);

    std::vector<bench_type> a(n);
    std::vector<bench_type> b(n);

    std::iota(a.begin(), a.end(), 1.0);

    bool dry = true;

    auto run_benches = [&dry, &a, &b] {
        test_exec_policy(dry, "seq", std::execution::seq, a, b);
        test_exec_policy(dry, "unseq", std::execution::unseq, a, b);
        test_exec_policy(dry, "par", std::execution::par, a, b);
        test_exec_policy(dry, "par_unseq", std::execution::par_unseq, a, b);
    };

    run_benches();
    std::cout << std::endl;
    dry = false;
    run_benches();
}
