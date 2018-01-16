#include <iostream>

template <class T>
struct Base {
	void operation() {
		std::cout << "- perform some general work in Base..." << std::endl;
		static_cast<T*>(this)->implementation();
		std::cout << "- more general work in Base..." << std::endl;
	}
};

struct Derived : Base<Derived> { // CRTP!
	void implementation() {
		std::cout << "! specialized work in Derived..." << std::endl;
	}
};

int main() {

	// this setup allows us to perform
	// polymorphism-like customization without dynamic dispatch!
	Derived d;
	d.operation();
}
