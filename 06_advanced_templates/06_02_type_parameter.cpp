#include <iostream>

template<typename T>
struct dimof {
	static constexpr int value = 0;
};
// the base template
// for the standard (non-array) case, the dimension is 0

template<typename T, int N>
struct dimof<T[N]> {
	static constexpr int value = 1 + dimof<T>::value;
};
// a partial specialization for types which can
// be written as "T[N]" (i.e. arrays)
// in this case we
//  - add 1 to our result value for this array dimension
//  - recursively invoke our metafunction by instantiating
//    the template for the remaining "T"

int main() {
	std::cout << "dimof<int>::value:           " << dimof<int>::value << std::endl;
	std::cout << "dimof<float[5]>::value:      " << dimof<float[5]>::value << std::endl;
	std::cout << "dimof<double[10][2]>::value: " << dimof<double[10][2]>::value << std::endl;
	std::cout << "dimof<char[3][2][2]>::value: " << dimof<char[3][2][2]>::value << std::endl;
}
