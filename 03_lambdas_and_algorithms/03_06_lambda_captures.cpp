#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>
#include <string>

bool true_for_any(const std::vector<double>& vec, std::function<bool(double)> condition) {
	for(auto v : vec) {
		if(condition(v)) return true;
	}
	return false;
}

bool has_value_between(const std::vector<double>& vec, double lower_bound, double upper_bound) {
	return true_for_any(vec, [lower_bound, upper_bound](double val) {
		return val >= lower_bound && val <= upper_bound;
	});
	// captures "lower_bound" and "upper_bound" by value (i.e. creates a copy)
	/// equivalent:
	//return true_for_any(vec, [=](double val) {
	//	return val >= lower_bound && val <= upper_bound;
	//});
	/// note:
	// [=] : default capture by value
	// [&] : default capture by reference
}

struct FullName {
	const std::string first;
	const std::string last;

	FullName(std::string first, std::string last)
		: first(first)
		, last(last)
	{}

	bool containsAnyName(std::vector<std::string> s) {
		return std::any_of(s.cbegin(), s.cend(), [&](const std::string& str) {
			return first == str || last == str;
		});
		// [&] captures "this" by reference (or rather, the pointer by value)

		/// the following does not work: (cannot capture members directly)
		//return std::any_of(s.cbegin(), s.cend(), [first, last](const std::string& str) {
		//	return first == str || last == str;
		//});

		/// this works -- captures the two relevant members by copy
		//return std::any_of(s.cbegin(), s.cend(), [f = first, l = last](const std::string& str) {
		//	return f == str || l == str;
		//});

		/// equivalent to the first option, but more explicit (still captures this by reference)
		//return std::any_of(s.cbegin(), s.cend(), [this](const std::string& str) {
		//	return first == str || last == str;
		//});

		/// by-copy capture of the current object (C++17)
		//return std::any_of(s.cbegin(), s.cend(), [*this](const std::string& str) {
		//	return first == str || last == str;
		//});
	}
};



