#include <iostream>
#include <climits>

template<int N>
struct t_abs {
	static_assert(N != INT_MIN);
	static constexpr int value = (N < 0) ? -N : N;
};

// t_abs is a template metafunction
// parameter = "N"
// return = "value"


int main() {
	std::cout << t_abs<-5>::value << std::endl;

	// "t_abs<-5>::value" is the equivalent to a call
	// -> it requests the value member for the
	//    instantiations with the given arguments (-5 here)
}
