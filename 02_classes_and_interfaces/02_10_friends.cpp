#include <string>
#include <iostream>

class F;

class Secret {
	std::string name;
	double weight;

	friend F;

  public:
	Secret(std::string name, double weight)
		: name(name)
		, weight(weight) {}
};

class F {
  public:
	void leakInformation(Secret s) {
		std::cout << s.name << ": " << s.weight << std::endl;
	}
};

int main() {

	Secret s{ "Peter", 60.0 };

	//std::cout << s.name << ": " << s.weight << std::endl;
	// Note: above does not compile

	F leaker;
	leaker.leakInformation(s);
}
