// note: this is currently not supported in MSVC 16.8

#include <concepts>
#include <cstddef>
#include <functional>

template <typename T>
concept Hashable = requires(T a) {
	std::hash<T>{}(a);
};

// Terse syntax

void fun(Hashable auto x) {}

// note: must be directly preceding auto:

void more_fun(const Hashable auto x) {}

// void less_fun(Hashable const auto x) {} // incorrect

int main() {
	// also applicable to variables!

	Hashable auto str = "Hello";
}
