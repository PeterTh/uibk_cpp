#include <initializer_list>
#include <algorithm>

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

// partial specialization for 2D Vectors :
// -- add x() and y() accessor member functions

template<typename ScalarType>
class Vector<ScalarType, 2> {
	ScalarType _x = 0, _y = 0;
	using TT = Vector<ScalarType, 2>;

  public:
	Vector() {}
	Vector(ScalarType x, ScalarType y) : _x(x), _y(y) {}

	ScalarType x() const { return _x; }
	ScalarType y() const { return _y; }

	ScalarType& x() { return _x; }
	ScalarType& y() { return _y; }

	ScalarType operator[](int idx) const {
		return idx == 0 ? _x : _y;
	}
	ScalarType& operator[](int idx) {
		return idx == 0 ? _x : _y;
	}
};

// works for any "Vector"s, including partially specialized ones:

template<typename ScalarType, int Length>
Vector<ScalarType, Length> operator+(const Vector<ScalarType, Length>& lhs, const Vector<ScalarType, Length>& rhs) {
	Vector<ScalarType, Length> ret;
	for(int i = 0; i < Length; ++i) {
		ret[i] = lhs[i] + rhs[i];
	}
	return ret;
}

using Vec2D = Vector<double, 2>;

int main(int argc, char** argv) {

	Vec2D one{ 1.0, 1.0 };
	Vec2D two{ 2.0, 2.0 };

	one.x();

	(one + two).y();
}
