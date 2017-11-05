
/// Textbook example

struct Vec2D {
	double x, y;
	Vec2D(double x, double y) : x(x), y(y) {}
};

class Shape {
  public:
	virtual double area() const = 0;
	virtual double circumference() const = 0;

	virtual void move(const Vec2D& v) = 0;
};
// Notes:
// - "virtual" to signify virtual member functions
//   (called depending on run-time type)
// - "const" after member function to indicate that
//   it does not change the object state (IMPORTANT)
// - " = 0" on a virtual member function means that it is *pure virtual*
//   -> must be implemented in derived in order for it to be complete

class Circle : public Shape {
	Vec2D center;
	double radius;

  public:
	Circle(Vec2D center, double radius)
		: center(center)
		, radius(radius) {}

	double area() const override { /* ... */ }
	double circumference() const override { /* ... */ }

	void move(const Vec2D& v) override { /* ... */ }
};
// Notes:
// - ": public Shape" means public inheritance from Shape
//   -> if members are publicly visible in Shape, they are also publicly visible in Circle
// - use the "override" keyword to indicate that
//   you want to override a base implementation (IMPORTANT)

class Rectangle : public Shape {
	Vec2D bottomLeft;
	Vec2D extents;

  public:
	Rectangle(Vec2D bottomLeft, Vec2D extents)
		: bottomLeft(bottomLeft)
		, extents(extents) {}

	double area() const override { /* ... */ }
	double circumference() const override { /* ... */ }

	void move(const Vec2D& v) override { /* ... */ }
};

class Square : public Rectangle {
  public:
	Square(Vec2D bottomLeft, double sideLength)
		: Rectangle(bottomLeft, Vec2D(sideLength, sideLength)) {}
};
// Notes:
// we are inheriting the *implementation* of "area",
// "circumference" and "move"
