#include <unordered_set>

#include <iostream>

struct Basic {
};

void unordered_set_test_fail() {
	//std::unordered_set<Basic> basic_set;
	//basic_set.insert(Basic());
	// note: here we encounter our second real C++ template error
	// let's see if we can do it in 5 minutes now
}


struct BasicHashable {
	int val;
};

bool operator==(BasicHashable a, BasicHashable b) {
	return a.val == b.val;
}

namespace std
{
	template<> struct hash<BasicHashable>
	{
		size_t operator()(const BasicHashable& s) const noexcept {
			return std::hash<int>{}(s.val);
		}
	};
}

void unordered_set_test() {
	std::unordered_set<BasicHashable> basic_hashable_set;

	basic_hashable_set.insert({ 8 });
	basic_hashable_set.insert({ 5 });
	basic_hashable_set.insert({ 42 });
	basic_hashable_set.insert({ 6 });
	basic_hashable_set.insert({ 7 });
	basic_hashable_set.insert({ 5 });

	for(auto cb : basic_hashable_set) {
		std::cout << cb.val << std::endl;
	}
}


int main() {
	unordered_set_test();
}
