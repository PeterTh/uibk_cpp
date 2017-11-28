#include <initializer_list>

template<typename ScalarType, int Length>
class Vector {
	using TT = Vector<ScalarType, Length>;

	ScalarType contents[Length];

public:
	Vector()
	{
		for(int i = 0; i < Length; ++i) contents[i] = 0;
	}
	Vector(std::initializer_list<ScalarType> init)
	{
		std::copy(init.begin(), init.end(), contents);
	}

	ScalarType operator[](int idx) const {
		return contents[idx];
	}
	ScalarType& operator[](int idx) {
		return contents[idx];
	}
};

template<typename ScalarType>
using Vector3 = Vector<ScalarType, 3>;


int main(int argc, char** argv) {
	Vector3<int> bla;
	// equivalent to
	Vector<int, 3> bla2;
}
