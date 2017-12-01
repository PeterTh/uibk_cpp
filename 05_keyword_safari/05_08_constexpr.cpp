
#include <iostream>

constexpr int fac(int n) {
	return n <= 1 ? 1 : (n * fac(n - 1));
}

// output function that requires a compile-time constant, for testing
template<int n>
struct constN {
	constN() { std::cout << n << '\n'; }
};

int main() {
	std::cout << "4! = ";
	constN<fac(4)> out1;
}

// https://godbolt.org/g/XoaGL9
