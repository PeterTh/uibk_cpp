#include <string>
#include <iostream>

class Bounds {
  public:
	Bounds(int min, int max)
		: min(min)
		, max(max) {}

  private:
        int min, max;

        friend std::ostream& operator<<(std::ostream& os, Bounds& b);
};

std::ostream& operator<<(std::ostream& os, Bounds& b) {
        return os << "[" << b.min << "," << b.max << "]";
}

class Foo {
};

int main() {
        Bounds b{1,5};

        std::cout << b << std::endl;

        Foo f;
        std::cout << f << std::endl;
}
