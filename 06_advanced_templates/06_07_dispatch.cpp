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

// Option 1: implement for each of them ///////////////////////////////////////

#if false
void dump(A a) {
	a.print_to(std::cerr);
}
void dump(B b) {
	b.print_to(std::cerr);
}
void dump(C c) {
	c.print_to(std::cerr);
}
void dump(D d) {
	std::cerr << d;
}
void dump(E e) {
	std::cerr << e;
}
#endif

// This works, but:
// - it heavily violates DRY (with all the resultant complications)
// - it needs to be manually extended whenever we want to dump a new class
// - it is deeply unsatisfactory

// Templates to the rescue? ///////////////////////////////////////////////////

#if false
template<typename T>
void dump(T t) {
	// ??? what now?
}
#endif

/// Option 2: templates + metaprogramming /////////////////////////////////////

// first, we need a way to identify our objects -> a metafunction

template<typename T, class = void>
struct has_print_to : public std::false_type {};

template<typename T>
struct has_print_to<T,
	std::void_t<decltype(std::declval<T>().print_to(std::declval<std::ostream&>()))>
> : public std::true_type {};

template<typename T>
constexpr bool has_print_to_v = has_print_to<T>::value;

#if false

// now we can write our template

template<typename T>
std::enable_if_t<has_print_to_v<T>> dump(T t) {
	t.print_to(std::cerr);
}
template<typename T>
std::enable_if_t<!has_print_to_v<T>> dump(T t) {
	std::cerr << t;
}

// Will work automatically for all classes matching the pattern

#endif 

/// Option 3: C++17 "if constexpr" ////////////////////////////////////////////

#if true

// We use the same "has_print_to" trait defined above, but skip enable_if

template<typename T>
void dump(T t) {
	if constexpr(has_print_to_v<T>) {
		t.print_to(std::cerr);
	} else {
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
