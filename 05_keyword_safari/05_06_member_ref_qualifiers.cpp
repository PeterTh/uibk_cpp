
class Vector {
	float contents[10];

  public:
	Vector() { }

	float operator[](int idx) const {
		return contents[idx];
	}
	float& operator[](int idx) {
		return contents[idx];
	}
};

void error() {

	float& ref = Vector()[5];
	ref = 7.f;
}


class SafeVector {
	float contents[10];

  public:
	SafeVector() { }

	float operator[](int idx) const && {
		return contents[idx];
	}
	float operator[](int idx) const & {
		return contents[idx];
	}
	float& operator[](int idx) & {
		return contents[idx];
	}
};

void safe() {
	//float& ref = SafeVector()[5];
	// ^ does not compile,
	// we can not access a reference from a temporary vector

	float val = SafeVector()[5];

	const SafeVector sv;
	sv[4];
}

