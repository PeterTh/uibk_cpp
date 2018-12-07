#include <vector>
#include <iostream>

class WriteOnlyMemory : private std::vector<double> {
	using base = std::vector<double>;
  public:
	using base::push_back;
	using base::emplace_back;
	using base::size;
};

namespace name {
	void foo(int i) { }
}

using namespace name;

int main() {

	foo(2);

	WriteOnlyMemory wom;

	wom.push_back(1.0);
	wom.emplace_back(2.0);

	std::cout << wom.size() << std::endl;

	wom.at(0);
}
