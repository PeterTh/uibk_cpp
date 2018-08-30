#include <iostream>

void test1() {

	int a = 5;

	// lambda version:

	{
		auto x = [a](int i) { return a*i; };
		std::cout << x(4) << std::endl;
	}

	// fully written out:

	{
		struct Unnamed1 {
			// captured by value -> field in struct
			int a;

			// NO DEFAULT CONSTRUCTOR

			// default copy / move semantics
			Unnamed1(const Unnamed1&) = default;
			Unnamed1(Unnamed1&&) = default;

			// not assignable
			Unnamed1& operator=(const Unnamed1&) = delete;

			// default destructor
			~Unnamed1() = default;

			// Call operator constructed from the lambda expression
			// operator is "const" because no "mutable" was specified for the lambda
			int operator()(int i) const constexpr {
				return a*i;
			}
		};

		auto x = Unnamed1{ a };
		x(4);
		std::cout << x(4) << std::endl;
	}
}


void test2() {

	int a = 5;
	float b = 5.0f;
	double c = 0.5f;

	// lambda version:

	{
		auto x = [a,&b,c](int i, const int& j) mutable noexcept {
			b *= (float)c;
			return a*i*j;
		};
		std::cout << x(4, 5) << std::endl;
		std::cout << b << std::endl;
	}

	// fully written out:

	{
		struct Unnamed {
			// captured by value -> field in struct
			int a;
			float& b; // OPTIONAL
			double c;

			// NO DEFAULT CONSTRUCTOR

			Unnamed(const Unnamed&) = default;
			Unnamed(Unnamed&&) = default;
			Unnamed& operator=(const Unnamed&) = delete;
			~Unnamed() = default;

			// Call operator constructed from the lambda expression
			// operator is not "const" because of "mutable"
			// operator is "noexcept" as it was declared in the lambda expression
			int operator()(int i, const int& j) noexcept constexpr {
				b *= (float)c;
				return a*i*j;
			}
		};

		auto x = Unnamed{ a, b, c };
		std::cout << x(4, 5) << std::endl;
		std::cout << b << std::endl;
	}
}

using fun_ptr_type = int(*)(int, int);

void test3() {

	// lambda version:

	{
		auto x = [](int i, int j) constexpr {
			return i*j;
		};
		std::cout << x(4, 5) << std::endl;
		int arr[x(1, 2)];
		fun_ptr_type fun = x;

	}

	// fully written out:

	{
		struct Unnamed {
			// NO DEFAULT CONSTRUCTOR

			Unnamed(const Unnamed&) = default;
			Unnamed(Unnamed&&) = default;
			Unnamed& operator=(const Unnamed&) = delete;
			~Unnamed() = default;

			operator fun_ptr_type() const {
				/* compiler defined */
				return (fun_ptr_type)0; /// NOTE: this is just to get it to compile, will crash
			}

			// Call operator constructed from the lambda expression
			// operator is "constexpr" as specified
			// note that as of C++17, the examples in test1 and test2 are also autoamtically "constexpr"
			int operator()(int i, int j) constexpr {
				return i*j;
			}
		};

		auto x = Unnamed{};
		std::cout << x(4, 5) << std::endl;
		int arr[x(1, 2)];
		fun_ptr_type fun = x;
	}
}


int main(int argc, char **argv) {
	test2();
}
