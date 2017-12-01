
#include <iostream>

struct Foo {
	// declaration of the static data member x
	static int x;

	int y;

	static int bla() {
		// we cannot access the non-static member y
		// in a static context
		return x;
	}

	void bar() {
		x += y;
	}
};

// definition of the static data member xg
int Foo::x = 2;


// inline static data members do not need to be defined
// separately -- see https://godbolt.org/g/gBSS7V
//struct Bar {
//	inline static int x;
//};


int main() {
	{
		// Calling a static member function by qualified name
		std::cout << "Foo::bla() : " << Foo::bla() << std::endl;

		// Calling a static member function with an instance
		Foo f;
		std::cout << "f.bla()   : " << f.bla() << std::endl;

		// both are equivalent
	}
	std::cout << std::endl;
	{
		// There is only one instance of the static data member
		Foo f;
		Foo g;

		std::cout << "f.x / g.x  : " << f.x << " / " << g.x << std::endl;
		f.x += 2;
		std::cout << "f.x / g.x  : " << f.x << " / " << g.x << std::endl;
	}
}
