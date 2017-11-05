#include <iostream>

class A {
	int i[32];
};

class B : public A { };
class C : public A { };
class D : public B, public C { };

void nonVirtualInheritance() {
	std::cout << "sizeof(A): " << sizeof(A) << std::endl;
	std::cout << "sizeof(B): " << sizeof(B) << std::endl;
	std::cout << "sizeof(C): " << sizeof(C) << std::endl;
	std::cout << "sizeof(D): " << sizeof(D) << std::endl;
	// Note: D clearly contains two instances of A!
	D d;
	D* dp = &d;
	B* dpb = dp;
	C* dpc = dp;
	//A* dpa = dp;
	// Note: the line above is ambiguous!
}

class Bv : virtual public A { };
class Cv : virtual public A { };
class Dv : public Bv, public Cv { };

void virtualInheritance() {
	std::cout << "sizeof(A): " << sizeof(A) << std::endl;
	std::cout << "sizeof(Bv): " << sizeof(Bv) << std::endl;
	std::cout << "sizeof(Cv): " << sizeof(Cv) << std::endl;
	std::cout << "sizeof(Dv): " << sizeof(Dv) << std::endl;
	// Note: a bit of extra memory (usually 1 pointer)
	//       in Bv and Cv for virtual inheritance, but no duplication
	Dv d;
	Dv* dp = &d;
	Bv* dpb = dp;
	Cv* dpc = dp;
	A* dpa = dp;
	// Note: the line above is no longer ambiguous!
}

int main() {
	nonVirtualInheritance();
	std::cout << "===" << std::endl;
	virtualInheritance();
}
