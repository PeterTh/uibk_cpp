#include <string>
#include <iostream>

class Bounds {
  public:
	Bounds(int min, int max)
		: min(min)
		, max(max) {}

  private:
        int min, max;

        friend std::ostream& operator<<(std::ostream& os, const Bounds& b);
};

std::ostream& operator<<(std::ostream& os, const Bounds& b) {
        return os << "[" << b.min << "," << b.max << "]";
}

class BoundsHidden {
  public:
	BoundsHidden(int min, int max) : min(min), max(max) {}

  private:
	int min, max;

	friend std::ostream& operator<<(std::ostream& os, const BoundsHidden& b) {
		return os << "[" << b.min << "," << b.max << "]";
	}
};

class Foo {
};

int main() {
        Bounds b{1,5};
        std::cout << b << std::endl;

		BoundsHidden bh{2,6};
		std::cout << bh << std::endl;

        //Foo f;
        //std::cout << f << std::endl;
}
