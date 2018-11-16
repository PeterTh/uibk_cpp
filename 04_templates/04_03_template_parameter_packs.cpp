#include <unordered_set>

#include <iostream>

// ---------------------------------------------- template type parameter pack

#if true

template <typename T>
T sum(T last) {
	return last;
}

template<typename T, typename ...Rest>
T sum(T t, Rest... rest) {
	return t + sum(rest...);
}

#else

// C++17 fold expression:

template<typename T, typename ...Rest>
T sum(T t, Rest... rest) {
	return (t + ... + rest);
}

#endif

// ---------------------------------------------- template template parameter pack
// ... left as an exercise


int main() {
	{
		std::cout << "sum(1, 2, 3, 10) : " << sum(1, 2, 3, 10) << std::endl;
		std::cout << "sum(1.0, 0.4, 0.1) : " << sum(1.0, 0.4, 0.1) << std::endl;
	}
}
