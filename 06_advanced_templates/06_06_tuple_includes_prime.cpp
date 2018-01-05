#include <iostream>
#include <tuple>

/// tools

template<bool VAL>
struct set_bool {
	static constexpr bool value = VAL;
};

struct true_type : public set_bool<true> {};
struct false_type : public set_bool<false> {};



/// first, we need a way to compare two types

template<typename T, typename U>
struct is_same : public false_type {};
template<typename T>
struct is_same<T, T> : public true_type {};

// We use partial specialization as a condition:
// - by default, types are not the same
// - iff both type arguments are the same ("is_same<T,T>")
//   we inherit from true_type to set our return "::value" to true

template<typename T, typename U>
constexpr int is_same_v = is_same<T, U>::value;



/// we also need a utility to see whether we are actually acting on a tuple

template<typename Test>
struct is_tuple : false_type {};
template<typename... Args>
struct is_tuple<std::tuple<Args...>> : true_type {};

template<typename T>
constexpr int is_tuple_v = is_tuple<T>::value;



/// now we can inspect the tuple

template<class Tuple, class T>
struct tuple_contains {
	static_assert(is_tuple_v<Tuple>, "tuple_contains called on non-tuple");
};

template<class T, class Head, class... Rest>
struct tuple_contains<std::tuple<Head, Rest...>, T> : public set_bool<
	is_same_v<Head, T> || tuple_contains<std::tuple<Rest...>, T>::value
> {};

template<class T>
struct tuple_contains<std::tuple<>, T> : public false_type {};

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
	std::cout << "tuple_contains_v<std::tuple<B>, B>:                    " << tuple_contains_v<std::tuple<int, B>, B> << std::endl;

	//std::cout << "\ntuple_contains_v<int, float>: " << tuple_contains_v<int, float> << std::endl;
	// ^^ No longer compiles, and with a nice error too
}
