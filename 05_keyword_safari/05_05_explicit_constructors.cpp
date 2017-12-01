#include <iostream>

struct Point {
	int x = 0, y = 0;

	Point() = default;
	Point(int p) : x(p), y(p) {}
};


struct FPoint {
	float x = 0, y = 0;

	FPoint() = default;
	explicit FPoint(float p) : x(p), y(p) {}
};

int main() {
	{
		Point p;
		int z = 7;
		// normal constructors with one argument are used
		// for *implicit conversion*
		p = z;
		std::cout << "p.x, p.y : " << p.x << ", " << p.y << std::endl;
		// this behavior can lead to situations
		// where erroneous program behaviour
		// is difficult to understand
	}

	{
		FPoint fp;
		float z = 7.f;

		// this line does not compile
		// "explicit" prevents the constructor from
		// being used for implicit conversion
		// fp = z;

		// this works, the cast invokes
		// explicit constructor conversion
		fp = (FPoint)z;

		// see: https://godbolt.org/g/fNN3Q4
	}
}
