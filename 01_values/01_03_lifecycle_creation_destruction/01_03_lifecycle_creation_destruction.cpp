
#include <iostream>

// a "struct" is just like a class, except for default visibility being "public"
struct C {
	int id;
	// constructor syntax
	C(int idParam) : id(idParam) {
		std::cout << "C " << id << " constructed" << std::endl;
	}
	// destructor syntax
	~C() {
		std::cout << "C " << id << " destroyed" << std::endl;
	}
};


int main() {

	C c1(1);

	C c2(2);

	{
		C c3(3);
	}

	if(C(4).id == 4) {
		C c(5);
	}

	C(6);

	C c(7);

}
