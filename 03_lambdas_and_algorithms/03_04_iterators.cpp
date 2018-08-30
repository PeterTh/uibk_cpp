#include <vector>
#include <map>
#include <string>
#include <iostream>

int main() {
	std::vector<int> vec{ 0,1,2,3,41,42 };

	// note: std::vector offers a contiguous iterator
	std::cout << *vec.begin() << std::endl;
	std::cout << *vec.rbegin() << std::endl;
	std::cout << *(vec.begin() + 2) << std::endl;
	std::cout << *(vec.rbegin() + 1) << std::endl;
	std::cout << "----" << std::endl;

	// when we are only reading, we should use the constant (c*) versions
	std::cout << *vec.cbegin() << std::endl;
	std::cout << *vec.crbegin() << std::endl;
	std::cout << *(vec.cbegin() + 2) << std::endl;
	std::cout << *(vec.crbegin() + 1) << std::endl;
	std::cout << "----" << std::endl;

	// we can apply std::distance, and in this case it will be of constant complexity
	std::cout << "dist: " << std::distance(vec.begin() + 2, vec.end()) << std::endl;
	std::cout << "----" << std::endl;

	// std::back_inserter is an iterator adapter
	auto inserter = std::back_inserter(vec);
	inserter++ = 55;
	inserter++ = 56;

	for(int v : vec) {
		std::cout << v << ", ";
	}
	std::cout << std::endl;

	for(auto it = std::make_reverse_iterator(vec.cend()); it != std::make_reverse_iterator(vec.cbegin()); it++) {
		std::cout << *it << ", ";
	}
	std::cout << std::endl;

	// there is a shorthand for that: vec.crend() / vec.crbegin();
}

