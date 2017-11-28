
#if true

int abs(int x) {
	return x > 0 ? x : -x;
}

float abs(float x) {
	return x > 0 ? x : -x;
}

double abs(double x) {
	return x > 0 ? x : -x;
}

char abs(char x) {
	return x > 0 ? x : -x;
}

// ...

#else

template<typename T>
T abs(T x) {
	return x > 0 ? x : -x;
}

#endif

int main() {
	int x = -7;
	x = abs(x);
	double y = -12.5;
	y = abs(y);
	float z = -0.25;
	z = abs(z);
}
