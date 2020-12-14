#include <concepts>
#include <cstddef>
#include <functional>

template <typename T>
concept Hashable = requires(T a) {
	std::hash<T>{}(a);
};

// can appear as the last element of a function declarator
template <typename T>
void f(T&&) requires Hashable<T>; 

// or right after a template parameter list
template <typename T>
requires Hashable<T> void g(T&&);

#if 1

// Kind-of-terse syntax

template<Hashable T>
void fun(T) {}

#else

// requires clause after signature is also possible

template<class T>
void fun(T) requires Hashable<T> {}

#endif

struct meow {};

int main() {
	fun(10); // OK, int satisfies Hashable
	//fun(meow{}); // Error: meow does not satisfy Hashable
}
