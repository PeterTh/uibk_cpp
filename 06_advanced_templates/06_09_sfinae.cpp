#include <iostream>
#include <string>

template<int N>
bool is_odd(int[1][N % 2 == 1 ? 1 : -1] = nullptr) {
	return true;
}

template<int N>
bool is_odd(int[1][N % 2 == 0 ? 1 : -1] = nullptr) {
	return false;
}

int main() {

	// int x[-1];
	// ^ this is a compiler error - we can't use a negative array length

	std::cout << "is_odd<0>()  : " << is_odd<0>() << std::endl;
	std::cout << "is_odd<1>()  : " << is_odd<1>() << std::endl;
	std::cout << "is_odd<33>() : " << is_odd<33>() << std::endl;
	std::cout << "is_odd<42>() : " << is_odd<42>() << std::endl;
}
