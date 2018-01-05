#include <type_traits>
#include <iostream>

template<typename T>
struct remove_const {
	using type = T;
};
// this primary template handles any type
// which is *not* const-qualified

template<typename T>
struct remove_const<const T> {
	using type = T;
};
// specialization for const-qualified types
// generates the type without qualification

struct A {};

int main() {

	static_assert(std::is_same<remove_const<int>::type, int>::value);

	static_assert(std::is_same<remove_const<const float>::type, float>::value);

	static_assert(std::is_same<remove_const<const A>::type, A>::value);

	static_assert(std::is_same<remove_const<volatile const int>::type, volatile int>::value);

	std::cout << "std::is_same<remove_const<int>::type, int>::value : "
		<< std::is_same<remove_const<int>::type, int>::value << std::endl;
	std::cout << "std::is_same<remove_const<const int>::type, const int>::value : "
		<< std::is_same<remove_const<const int>::type, const int>::value << std::endl;
}


