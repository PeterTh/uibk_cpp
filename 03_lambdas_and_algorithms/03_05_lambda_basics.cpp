#include <vector>
#include <functional>
#include <iostream>

void apply_to_all(std::vector<double>& vec, std::function<double(double)> fun) {
	for(auto& element : vec) {
		element = fun(element);
	}
}

int main(int argc, char** argv) {

	auto add = [](int a, int b) {
		return a + b;
	};
	int sum = add(5, 6);

	auto mul = [](int a, int b) -> int {
		return a * b;
	};
	/// Note: " -> int" explicitly defines the return type of the lambda
	/// it is only necessary if there are multiple "return" statements without a unique return type

	std::vector<double> values { 1.0, 2.0, 4.0, 8.0 };

	apply_to_all(values, [](double value) {
		return value*value;
	});

	for(auto v : values) {
		std::cout << v << ", ";
	}
	std::cout << std::endl;
}
