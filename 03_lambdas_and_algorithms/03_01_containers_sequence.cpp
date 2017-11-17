#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>

#include <iostream>

struct Traced {
	Traced() { std::cout << "Traced #" << this << " constructed.\n"; }
	~Traced() { std::cout << "Traced #" << this << " destroyed.\n"; }
	Traced(const Traced& other) { std::cout << "Traced #" << this << " copy constructed from " << &other << ".\n"; }
	Traced(Traced&& other) noexcept { std::cout << "Traced #" << this << " move constructed from " << &other << ".\n"; }
	Traced& operator=(const Traced& other) { std::cout << "Traced #" << this << " copy assigned to from " << &other << ".\n"; return *this; }
	Traced& operator=(Traced&& other) noexcept { std::cout << "Traced #" << this << " move assigned to from " << &other << ".\n"; return *this; }
};

void array_test() {

	// array of 10 "double" values
	std::array<double, 10> double_values{ 0.0 };
	// note that "10" needs to be a compile-time constant value

	// array of 3 "Traced" values
	std::cout << "1 ---- Before traced_array" << std::endl;
	std::array<Traced, 3> traced_array;
	std::cout << "2 ---- Before auto traced_copy = traced_array" << std::endl;
	auto traced_copy = traced_array;
	std::cout << "3 ---- Before traced_copy = traced_array" << std::endl;
	traced_copy = traced_array;
	std::cout << "4 ---- Before end of array_test" << std::endl;

	// note the value semantics, unlike C-style arrays!
}

void vector_test() {

	std::cout << "0 ---- Before traced_vector" << std::endl;
	std::vector<Traced> traced_vector;
	std::cout << "1 ---- Before traced_vector.reserve(2)" << std::endl;
	traced_vector.reserve(2);
	std::cout << "2 ---- Before traced_vector.push_back" << std::endl;
	traced_vector.push_back(Traced());
	std::cout << "3 ---- Before traced_vector.emplace_back" << std::endl;
	traced_vector.emplace_back();
	std::cout << "4 ---- Before traced_vector.emplace_back (3rd element)" << std::endl;
	traced_vector.emplace_back();
	std::cout << "5 ---- Before end of vector_test" << std::endl;

	// note that having to resize the vector implies copying (or moving) all existing elements!
}

void various_list_test() {
	std::deque<Traced> traced_deque;
	// a double-ended queue with indexed access
	// e.g. traced_deque[0] is possible (though invalid since the deque is empty)

	std::list<Traced> traced_list;
	// a doubly linked list (no indexed access)

	std::forward_list<Traced> traced_forward_list;
	// a single-linked-list (no indexed access)
	// more space-efficient than the above, useful if bidirectional iteration is not required
}


int main() {
	//array_test();
	vector_test();
}
