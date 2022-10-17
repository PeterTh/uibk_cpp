// you can see this example working with recent GCC and Clang versions here:
// https://godbolt.org/z/WzFsJp

#include <algorithm>
#include <type_traits>
#include <tuple>

template<typename ScalarType, int Length>
class Vector {
	ScalarType contents[Length];

public:
	template<typename ...Args>
	Vector(Args... args)
	{
		auto init = {args...};
		std::copy(init.begin(), init.end(), contents);
	}
};

template<int N, typename... Ts> using NthTypeOf =
        typename std::tuple_element<N, std::tuple<Ts...>>::type;

// deduction guide for template "Vector":

template<typename ...Args>
Vector(Args... args) -> Vector<NthTypeOf<0, Args...>, sizeof...(Args)>;

int main(int argc, char** argv) {
	Vector one{ 1.0, 1.0, 1.0 };
	static_assert(std::is_same_v<decltype(one), Vector<double, 3>>);

	Vector two{ 2, 2 };
	static_assert(std::is_same_v<decltype(two), Vector<int, 2>>);
}
