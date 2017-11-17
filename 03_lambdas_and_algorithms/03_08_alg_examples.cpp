#include <iostream>
#include <vector>
#include <algorithm>

bool has_duplicates(std::vector<int> v) {
	std::sort(v.begin(), v.end());
	return std::adjacent_find(v.begin(), v.end()) != v.end();
}

bool has_elements_closer_than(std::vector<int> v, int range) {
	std::sort(v.begin(), v.end());
	return std::adjacent_find(v.begin(), v.end(), [range](int l, int r) {
		return abs(l - r) < range;
	}) != v.end();
}

std::vector<int> select_even(const std::vector<int>& v) {
	std::vector<int> ret;
	std::copy_if(v.cbegin(), v.cend(), std::back_inserter(ret), [](int num) {
		return num % 2 == 0;
	});
	return ret;
}


int main(int argc, char** argv) {

	{
		std::vector<int> v1{ 1,2,3,42,5 };
		std::cout << "has_duplicates(v1) : " << has_duplicates(v1) << std::endl;
	}
	{
		std::vector<int> v2{ 1,2,3,42,5,2 };
		std::cout << "has_duplicates(v2) : " << has_duplicates(v2) << std::endl;
	}

	{
		std::vector<int> v1{ 1,2,3,42,5 };
		std::cout << "has_elements_closer_than(v1, 2) : " << has_elements_closer_than(v1, 2) << std::endl;
	}
	{
		std::vector<int> v3{ 42,1,20,30,50 };
		std::cout << "has_elements_closer_than(v3, 2) : " << has_elements_closer_than(v3, 2) << std::endl;
		std::cout << "has_elements_closer_than(v3, 9) : " << has_elements_closer_than(v3, 9) << std::endl;
	}

	{
		std::vector<int> v1{ 1,2,3,42,5 };
		auto even = select_even(v1);
		std::cout << "select_even(v1) : ";
		for(auto i : even) { std::cout << i << ", "; }
		std::cout << std::endl;
	}
}
