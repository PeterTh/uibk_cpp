#include <iostream>

/// Scenario: /////////////////////////////////////////////////////////////////
// we have lots of classes in our project
// (maybe from different libraries)
// - some can be printed with a "print_to" member function
// - some can be printed using operator<< on a std stream
// - they are not part of any hierarchy or specifically tagged

struct A {
	void print_to(std::ostream& o) {
		o << "A\n";
	}
};
struct B {
	void print_to(std::ostream& o) {
		o << "B\n";
	}
};
struct C {
	void print_to(std::ostream& o) {
		o << "C\n";
	}
};
struct D {
};
std::ostream& operator<<(std::ostream& o, D) {
	return o << "D\n";
}
struct E {
};
std::ostream& operator<<(std::ostream& o, E) {
	return o << "E\n";
}

// not printable with either method
struct F {};

/// Goal: we want to be able to dump all these for some error reporting ///////

template<class T>
concept stream_printable =
    requires(T t, std::ostream& o) { o << t; };

template<stream_printable T>
void dump(T t) {
	std::cerr << t;
}

template <class T>
concept print_to_printable = 
	requires(T t, std::ostream& o) { t.print_to(o); };

template<print_to_printable T>
void dump(T t) {
	t.print_to(std::cerr);
}

/// Usage test  ///////////////////////////////////////////////////////////////

int main() {
	A a;
	B b;
	C c;
	D d;
	E e;
	F f;

	dump(a);
	dump(b);
	dump(c);
	dump(d);
	dump(e);
//	dump(f); // automatically get useful errors -- at the call site!
}
