#include <type_traits>
#include <iostream>

/// 1 -- Refactoring / Conventions for metafunctions returning a type

template<typename T>
struct set_type {
	using type = T;
};

// Refactoring: use inheritance to set the result type member:

template<typename T>
struct remove_const : set_type<T> {};
template<typename T>
struct remove_const<const T> : set_type<T> {};

// Refactoring: create a alias template to save writing ::type everywhere
// Convention: this has the suffix "_t"

template<typename T>
using remove_const_t = typename remove_const<T>::type;
// note: "typename" here disambiguates the parsing; no longer required in C++20



/// 2 -- Refactoring / Conventions for metafunctions returning a value

template<int VAL>
struct set_int {
	static constexpr int value = VAL;
};

template<typename T>
struct dimof : set_int<0> {};
template<typename T, int N>
struct dimof<T[N]> : set_int<1 + dimof<T>::value> {};

// Refactoring: create a *variable* template to save writing ::value everywhere
// Convention: this has the suffix "_v"

template<typename T>
constexpr int dimof_v = dimof<T>::value;



/// -- Usage - note that the standard library "is_same" also follows this convention

struct A {};

int main() {

	static_assert(std::is_same_v<remove_const_t<int>, int>);
	static_assert(std::is_same_v<remove_const_t<const float>, float>);
	static_assert(std::is_same_v<remove_const_t<const A>, A>);
	static_assert(std::is_same_v<remove_const_t<volatile const int>, volatile int>);

	std::cout << "dimof_v<int>:           " << dimof_v<int> << std::endl;
	std::cout << "dimof_v<float[5]>:      " << dimof_v<float[5]> << std::endl;
	std::cout << "dimof_v<double[10][2]>: " << dimof_v<double[10][2]> << std::endl;
	std::cout << "dimof_v<char[3][2][2]>: " << dimof_v<char[3][2][2]> << std::endl;
}
