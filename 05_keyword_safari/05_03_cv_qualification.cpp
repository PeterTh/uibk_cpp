
void take_int_ref(int& i) {}

void take_int_const_ref(const int& i) {}

void take_int_volatile_ref(volatile int& i) {}

void take_int_const_volatile_ref(const volatile int& i) {}


int main() {

	int x = 0;
	const int cx = 0;
	volatile int vx = 0;
	const volatile int cvx = 0;

	take_int_ref(x);
	// take_int_ref(cx);    // impossible -> target less qualified
	// take_int_ref(vx);    // impossible -> target less qualified
	// take_int_ref(cvx);   // impossible -> target less qualified

	take_int_const_ref(x);  // fine! implicit conversion to more qualified target
	take_int_const_ref(cx);
	// take_int_const_ref(vx);  // impossible -> target less qualified
	// take_int_const_ref(cvx); // impossible -> target less qualified

	take_int_volatile_ref(x);  // fine! implicit conversion to more qualified target
	// take_int_volatile_ref(cx);  // impossible -> target less qualified
	take_int_volatile_ref(vx);
	// take_int_volatile_ref(cvx); // impossible -> target less qualified

	take_int_const_volatile_ref(x);   // fine! implicit conversion to more qualified target
	take_int_const_volatile_ref(cx);  // fine! implicit conversion to more qualified target
	take_int_const_volatile_ref(vx);  // fine! implicit conversion to more qualified target
	take_int_const_volatile_ref(cvx);


	/// Syntax note: for more complicated pointer types, read qualifiers right to left
	const int *p1; // pointer to const int
	int const *p2; // pointer to const int
	int * const p3 = nullptr; // const pointer to int
	int const * const p4 = nullptr; // const pointer to const int

	int volatile * const * volatile p5; // volatile pointer to a const pointer to a volatile integer value

}
