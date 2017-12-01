#include <iostream>

struct Trace {
	Trace() { std::cout << "Creating Trace at " << this << std::endl; }
	~Trace() { std::cout << "Destructor for Trace at " << this << std::endl; }
};

void foo() {
	std::cout << "Beginning of foo()" << std::endl;
	static Trace a;
	std::cout << "Middle of foo()" << std::endl;
	Trace b;
	std::cout << "End of foo()" << std::endl;
}


int main() {
	std::cout << "-------- main(), Before first foo() call" << std::endl;
	foo();
	std::cout << "-------- main(), Between foo() calls" << std::endl;
	foo();
	std::cout << "-------- main(), End" << std::endl;
}
