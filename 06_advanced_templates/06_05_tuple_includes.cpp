#include <iostream>
#include <tuple>

/// tools

template<bool VAL>
struct set_bool {
	static constexpr bool value = VAL;
};

struct true_type : set_bool<true> {};
struct false_type : set_bool<false> {};


/// first, we need a way to compare two types

template<typename T, typename U>
struct is_same : false_type {};
template<typename T>
struct is_same<T,T> : true_type {};

// We use partial specialization as a condition:
// - by default, types are not the same
// - iff both type arguments are the same ("is_same<T,T>")
//   we inherit from true_type to set our return "::value" to true

template<typename T, typename U>
constexpr int is_same_v = is_same<T, U>::value;


/// now we can inspect the tuple

template<class Tuple, class T>
struct tuple_contains : false_type {
};
// the base case -- we don't have the element

template<class T, class Head, class... Rest>
struct tuple_contains<std::tuple<Head, Rest...>, T> : set_bool<
	is_same_v<Head, T> || tuple_contains<std::tuple<Rest...>, T>::value
> {};
// step case -- recursion

template<typename T, typename U>
constexpr int tuple_contains_v = tuple_contains<T, U>::value;



/// -- Usage - note that the standard library "is_same" also follows this convention

struct B {};

int main() {
	std::cout << "tuple_contains_v<std::tuple<>, float>:                 " << tuple_contains_v<std::tuple<>, float> << std::endl;
	std::cout << "tuple_contains_v<std::tuple<int, char, float>, float>: " << tuple_contains_v<std::tuple<int, char, float>, float> << std::endl;
	std::cout << "tuple_contains_v<std::tuple<int, B>, B>:               " << tuple_contains_v<std::tuple<int, B>, B> << std::endl;
	std::cout << "tuple_contains_v<std::tuple<int, B>, int>:             " << tuple_contains_v<std::tuple<int, B>, int> << std::endl;
	std::cout << "tuple_contains_v<std::tuple<int, B>, float>:           " << tuple_contains_v<std::tuple<int, B>, float> << std::endl;

	std::cout << "\ntuple_contains_v<int, float>: " << tuple_contains_v<int, float> << std::endl;
	// ^^ HMMMMM
	// do we really want this to compile?
}
