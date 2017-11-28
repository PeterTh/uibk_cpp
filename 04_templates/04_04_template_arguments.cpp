#include <iostream>
#include <vector>
#include <list>

template<typename T>
T abs(T x) {
	return x > 0 ? x : -x;
}

template<typename T, typename In>
T num_cast(In v) {
	return (T)v;
}

template<template<typename, typename> class ListTT = std::vector>
ListTT<int, std::allocator<int>> create_sequence(int a, int b, int c) {
	return { a, b, c };
}

int main() {
	abs(5); // argument type implicitly deduced as "int" from calling context
	abs<double>(5); // template argument explicitly specified as double

	int x = 0;
	double y = num_cast<double>(x);
	float z = num_cast<float>(y);
	// first template argument for num_cast needs to be explicit;
	// cannot be deduced from the function arguments at the call site

	auto vec = create_sequence(1, 2, 3);
	// "vec" is a "std::vector<int>" due to the
	// defaulted template template parameter
	auto list = create_sequence<std::list>(2, 3, 4);
	// "list" is a "std::list<int>"

}
