
#include <iostream>

// we read "int&" as "integer reference"
void f_int(int& i) {
	i = 5;
}

class Cls {
  public:
	Cls(int i) : mem(i) {
	}
	int mem;
};

// we read "Cls&" as "Cls reference" or "Reference to an object of type Cls"
void f_cls(Cls& c) {
	c.mem = 5;
}


int main() {

	int x = 0;
	f_int(x);
	// what is the value of x?

	Cls c(0);
	f_cls(c);
	// what is the value of c.mem?

	// let's find out
	std::cout << "x: " << x << std::endl;
	std::cout << "c.mem: " << c.mem << std::endl;

	return 0;
}

