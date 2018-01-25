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

/// Goal: we want to be able to dump all these for some error reporting ///////

#include <boost/hana.hpp>
namespace hana = boost::hana;

template<typename T>
void dump(T t) {
	hana::if_(hana::is_valid([](auto t) -> decltype(t.print_to(std::cerr)) {})(t),
		[](auto&& t) { t.print_to(std::cerr); },
		[](auto&& t) { std::cerr << t; }
	)(std::forward<T&&>(t));
}

// C++ 17:

#if 0
template<typename T>
void dump(T t) {
	if constexpr(hana::is_valid([](auto t) -> decltype(t.print_to(std::cerr)) {})(t)) {
		t.print_to(std::cerr);
	}
	else {
		std::cerr << t;
	}
}
#endif

/// Usage test  ///////////////////////////////////////////////////////////////

int main() {
	A a;
	B b;
	C c;
	D d;
	E e;

	dump(a);
	dump(b);
	dump(c);
	dump(d);
	dump(e);
}
