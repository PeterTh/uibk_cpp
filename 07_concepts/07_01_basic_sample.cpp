#include <concepts>
#include <cstddef>
#include <functional>
#include <string>
using namespace std::literals;

// Declaration of the concept "Hashable", which is satisfied by
// any type 'T' such that for values 'a' of type 'T',
// the expression std::hash<T>{}(a) compiles
template <typename T>
concept Hashable = requires(T a) {
	std::hash<T>{}(a);
};

template<typename T>
	requires Hashable<T> 
void fun(T) {
	// ... internal code
	std::hash(T);
	// ... internal code
}

struct meow {};

int main() {
	fun("abc"s); // OK, std::string satisfies Hashable
	fun(meow{}); // Error: meow does not satisfy Hashable
}
