#include <initializer_list>
#include <algorithm>

template<typename ScalarType, int Length>
class Vector {
	ScalarType contents[Length] = {};

  public:
	Vector() {}
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

	Vector operator+(const Vector& other) const {
		Vector ret;
		for(int i = 0; i < Length; ++i) {
			ret[i] = contents[i] + other[i];
		}
		return ret;
	}
};

using Vec3D = Vector<double, 3>;

int main(int argc, char** argv) {

	Vec3D zero;
	Vec3D one{ 1.0, 1.0, 1.0 };

	zero + one;
}
