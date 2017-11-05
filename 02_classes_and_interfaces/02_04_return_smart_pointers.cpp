#include <iostream>
#include <memory>

struct ComplexNonMoveableThing {
	ComplexNonMoveableThing() {
		std::cout << "created ComplexNonMoveableThing #" << this << "." << std::endl;
	}
	~ComplexNonMoveableThing() {
		std::cout << "destroyed ComplexNonMoveableThing #" << this << "." << std::endl;
	}
	ComplexNonMoveableThing(const ComplexNonMoveableThing& from) {
		std::cout << "copy constructed ComplexNonMoveableThing #" << this << " from #" << &from << "." << std::endl;
	}
	//ComplexNonMoveableThing(const ComplexNonMoveableThing& from) = delete;

	//ComplexNonMoveableThing(ComplexNonMoveableThing&&) = delete;
};

/// What options do we have to return a "ComplexNonMoveableThing" ?

/// 1; Best if not too expensive or impossible to copy
ComplexNonMoveableThing createComplexNonMoveableThing1() {
	ComplexNonMoveableThing res;
	return res;
}

/// 2; "Classic" C++
// needs passing in at call site of pre-allocated structure
// do NOT use in most cases
void createComplexNonMoveableThing2(ComplexNonMoveableThing& output) {
}

/// 3; std::unique_ptr
// best choice if a simple value does not work
// lifetime is controlled by the unique_ptr's lifetime
std::unique_ptr<ComplexNonMoveableThing> createComplexNonMoveableThing3() {
	return std::make_unique<ComplexNonMoveableThing>();
}

/// 4; std::shared_ptr
// *only* if you know that ownership for this will generally be shared
// otherwise, use a unique_ptr
std::shared_ptr<ComplexNonMoveableThing> createComplexNonMoveableThing4() {
	return std::make_shared<ComplexNonMoveableThing>();
}

int main() {

	{
		std::cout << "i1 block" << std::endl;
		auto instance1 = createComplexNonMoveableThing1();
		std::cout << "i1 block end" << std::endl;
	}

	std::cout << "------ 1" << std::endl;

	{
		std::cout << "i2 block" << std::endl;
		ComplexNonMoveableThing instance2;
		createComplexNonMoveableThing2(instance2);
		std::cout << "i2 block end" << std::endl;
	}

	std::cout << "------ 2" << std::endl;

	{
		std::cout << "i3 block" << std::endl;
		auto instance3 = createComplexNonMoveableThing3();
		std::cout << "i3 block end" << std::endl;
	}

	std::cout << "------ 3" << std::endl;

	{
		std::cout << "i4 block" << std::endl;
		auto instance4 = createComplexNonMoveableThing4();
		std::cout << "i4 block end" << std::endl;
	}

	std::cout << "------ 4" << std::endl;
}

