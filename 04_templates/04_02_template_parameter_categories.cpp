#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <list>



// Non-type template parameters

template<int I, int N>
double get_element(std::array<double,N> arr) {
	static_assert(I >= 0 && I < N, "Array access out of bounds");
	return arr[I];
}



// Type template parameters

template<typename P, typename F>
P apply_function(P input, F function) {
	return function(input);
}



// Template template parameters

template<template<typename,typename> class TT, typename T, typename A>
void output(const TT<T,A>& container) {
	for(auto& element : container) {
		std::cout << element << ", ";
	}
	std::cout << std::endl;
}



int main() {
	{
		std::array<double, 15> arr{ {0} };
		get_element<7>(arr);

		//get_element<-1>(arr);
		//get_element<17>(arr);
	}
	std::cout << "---" << std::endl;
	{
		int x = 5;
		int result = apply_function(x, [](int v) { return v * 2; });
		std::cout << x << " -> " << result << std::endl;
	}
	{
		std::string x = "Hello";
		std::string result = apply_function(x, [](std::string v) { return v + " world"; });
		std::cout << x << " -> " << result << std::endl;
	}
	std::cout << "---" << std::endl;
	{
		std::vector<int> v1{ 1,2,3,4 };
		output(v1);
	}
	{
		std::list<std::string> v2{ "Bla", "Alb", "Xyz"};
		output(v2);
	}
}
