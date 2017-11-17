#include <set>
#include <map>

#include <iostream>

struct Basic {
};

void set_test_fail() {
	std::set<Basic> basic_set;
	// note: this compiles (!)

	//basic_set.insert(Basic());
	// note: here we encounter our first real C++ template error
	// let's talk about what goes wrong here for a quarter of an hour
}


struct ComparableBasic {
	int val;
};
bool operator<(ComparableBasic a, ComparableBasic b) noexcept {
	return a.val < b.val;
}

void set_test() {
	std::set<ComparableBasic> comp_set;

	comp_set.insert({ 19 });
	comp_set.insert({ 5 });
	comp_set.insert({ 7 });
	comp_set.insert({ 5 });

	for(auto cb : comp_set) {
		std::cout << cb.val << std::endl;
	}
}


void map_test() {
	std::map<ComparableBasic, double> test_map;

	test_map[{5}] = 5.0;
	test_map[{42}] = 1.0;
	test_map[{5}] = 7.0;

	for(auto entry : test_map) {
		std::cout << entry.first.val << " : " << entry.second << std::endl;
	}
	std::cout << std::endl;
}


int main() {
	//set_test();
	map_test();
}
