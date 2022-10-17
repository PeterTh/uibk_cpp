#include <iostream>
#include <iomanip>

namespace bla {

	struct Vec2D {

		double x, y;

		Vec2D(double x, double y) : x(x), y(y) {}

		Vec2D operator+(Vec2D other) const {
			return { x + other.x, y + other.y };
		}

		Vec2D operator*(double factor) const {
			return { x*factor, y*factor };
		}
	};

	std::ostream& operator<<(std::ostream& stream, Vec2D v) {
		return stream << "( " << std::setw(8) << v.x << " , " << std::setw(8) << v.y << " )";
	}

	void basicOps() {
		Vec2D a{ 1.0, 5.0 };

		std::cout << "a     : " << a << std::endl;
		std::cout << "a+a   : " << a + a << std::endl;
		std::cout << "a*0.5 : " << a*0.5 << std::endl;

		//std::cout << "0.5*a : " << 0.5*a << std::endl;
		// Note: above doesn't work!
	}

	Vec2D operator*(double factor, Vec2D vec) {
		return vec*factor;
	}

	void doSomethingWith(Vec2D v) {}

	void doSomethingWithout() {}

} // end namespace

void standaloneOps() {
	// note: we need to use the namespace qualification here
	bla::Vec2D b{ 3.0, 2.0 };
	// ... and here
	bla::doSomethingWithout();
	// but not here! argument-dependent lookup
	doSomethingWith(b);

	std::cout << "b     : " << b << std::endl;
	std::cout << "0.5*b : " << 0.5*b << std::endl;
	// Now it works
}

int main() {
	bla::basicOps();
	//standaloneOps();
}
