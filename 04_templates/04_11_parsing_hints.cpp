#include <iostream>

/// Dependent name

template<typename T>
void dependent() {

	T::print<5>();
	// ^ this should not work:
	// since the name is dependent, it's unclear at
	// parse time whether it is a template
	// -> parsed as an expression

	//T::template print<5>();
	// ^ disambiguate by writing "template" before the templated call
}

struct Bar {
	template<int N>
	static void print() {
		std::cout << N << std::endl;
	}
};

/// Usage

int main() {
	dependent<Bar>();
}
