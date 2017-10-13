
#include <iostream>

struct C {
	C() {
		std::cout << "C#" << this << " constructed" << std::endl;
	}
	~C() {
		std::cout << "C#" << this << " destroyed" << std::endl;
	}
	// copy constructor syntax
	C(const C& from) {
		std::cout << "C#" << this << " constructed from C#" << &from << std::endl;
	}

};


void takeC(C c) {
	std::cout << "We are in takeC" << std::endl;
}

C returnC() {
	std::cout << "We are in returnC" << std::endl;
	C c;
	std::cout << "We are leaving returnC" << std::endl;
	return c;
}

int main() {

	C val;

	C c101(val);

	takeC(val);

	returnC();
}
