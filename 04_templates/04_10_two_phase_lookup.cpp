#include <iostream>

/// Non-dependent name

void foo(void*) {
	std::cout << "foo(void*)" << std::endl;
}

template<typename T>
void non_dependent() {
	foo(0);
}

void foo(int) {
	std::cout << "foo(int)" << std::endl;
}

/// Dependent name

template<typename T>
void dependent() {
	T::bar();
}

struct Bar {
	static void bar() {
		std::cout << "bar" << std::endl;
	}
};

/// Usage

int main() {
	non_dependent<float>();

	// on Visual C++ up to and including 17, without the /fpermissive- switch, this will print
	// "foo(int)"
	// on conformant C++ compilers, it will print
	// "foo(void*)"

	// foo(0); is a non-dependent call, which means that it
	// should be looked up in the first phase, while the template
	// definition is parsed. At that point, foo(int) is not part of
	// the available overload set

	dependent<Bar>();

	// Bar::bar is found even though it does not exist at the
	// point where the template is defined
}
