// adapted from boost::bimap example

#include <string>
#include <iostream>

#include "boost/bimap.hpp"

// helper to print maps
template<class MapType>
void print_map(const MapType& map, const std::string& separator, std::ostream& os) {
	for(auto p : map) {
		os << p.first << separator << p.second << std::endl;
	}
}

int main() {
	boost::bimap<std::string, int> results;
	results.insert({ "Argentina", 1 });
	results.insert({ "Spain"    , 2 });
	results.insert({ "Germany"  , 3 });
	results.insert({ "France"   , 4 });

	std::cout << "The number of countries is " << results.size() << std::endl;

	std::cout << "Germany ended up in position " << results.left.at("Germany") << std::endl;
	// ^ map lookup by left-hand side
	std::cout << "The winner is " << results.right.at(1) << std::endl << std::endl;
	// ^ map lookup by right-hand side

	std::cout << "Countries names ordered by their final position:" << std::endl;
	print_map(results.right, ") ", std::cout);
	// ^ results.right works like a std::map<int, std::string>
	std::cout << std::endl;

	std::cout << std::endl << "Countries names ordered alphabetically along with their final position:" << std::endl;
	print_map(results.left, " ends in position ", std::cout);
	// ^ results.left works like a std::map<std::string, int>
	std::cout << std::endl;
}
