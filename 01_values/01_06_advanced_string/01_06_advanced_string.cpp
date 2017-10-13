
#include <stdlib.h>
#include <string.h>

/// Note:
/// this is a very C-style example, to make the concept of move semantics and r-value references easier to understand

struct string
{
	char* data;

	string(const char* p) {
		size_t size = strlen(p) + 1;
		data = new char[size];
		memcpy(data, p, size);
	}

	~string() {
		delete[] data;
	}

	string(const string& from) {
		size_t size = strlen(from.data) + 1;
		data = new char[size];
		memcpy(data, from.data, size);
	}
};

string funReturningString() {
	return string("Foo");
}

int main() {

	string x("Bla");

	string a(x);
	// we need a copy, program could look at x later
	string c(funReturningString());
	// we *don't* need a copy, but still have to make one

}
