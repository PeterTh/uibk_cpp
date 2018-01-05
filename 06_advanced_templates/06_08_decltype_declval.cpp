#include <iostream>
#include <string>

int fun(); // NOTE: "fun" has no body
// -> using it in an evaluated context would be an error

int main() {

	decltype(5u + 7u) y;
	// equivalent to "unsigned y;"

	decltype(std::declval<float>() * std::declval<double>()) z;
	// equivalent to "double z;"

	decltype(std::declval<std::string>().cbegin()) iterator;
	// equivalent to "std::string::const_iterator iterator;"

	decltype(fun()) x;
	// equivalent to "int x;"
	// we can use fun here since it is an unevaluated context

	std::cout << sizeof(fun()) << std::endl;
	// also allowed -- also an unevaluated context

	// fun();
	// ^ this causes a linker error (used in evaluated context)
}
