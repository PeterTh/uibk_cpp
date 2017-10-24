#include <string>

using std::string;

// FIRST EXAMPLE //////////////////////////////////////////////////////////////

// very bad:

string searchAndReplace(string in, string toReplace, string replacement,
                        bool ignoreCase, bool replaceAll, bool transformBackslash, bool isRegex) {
	// ...
}

// one option - group parameters and make them descriptive at the call site:

enum class ReplaceParameters {
	IGNORE_CASE = 0b0001,
	REPLACE_ALL = 0b0010,
	TRANSFORM_BACKSLASH = 0b0100,
	IS_REGEX = 0b1000,
};

string searchAndReplace(string in, string toReplace, string replacement, ReplaceParameters params) {
	// this is better in terms of self-documentation, but might end up with a large function
	// ...
}

// But we can do better:
// 1) for some flags, a better option is often to create multiple functions
// 2) we can implicitly encode some information in the type of the arguments and resolve it by overloading
// 3) some functionality does not need to be part of the same single function

struct Regex {
	Regex(string s) { }
	// ...
};

struct StringIgnoringCase {
	StringIgnoringCase(string s) { }
	// ...
};

string transformBackslashes(string in) { }

string searchAndReplaceFirst(string in, string toReplace, string replacement) { }
string searchAndReplaceFirst(string in, Regex toReplace, string replacement) { }
string searchAndReplaceFirst(string in, StringIgnoringCase toReplace, string replacement) { }

string searchAndReplaceAll(string in, string toReplace, string replacement) { }
string searchAndReplaceAll(string in, Regex toReplace, string replacement) { }
string searchAndReplaceAll(string in, StringIgnoringCase toReplace, string replacement) { }

// NOTE: if these functions share all or part of their implementation, you
// can and should do so internally without changing the interface

// SECOND EXAMPLE /////////////////////////////////////////////////////////////

// bad:

bool doRaysCollide(float x1, float y1, float z1, float dx1, float dy1, float dz1,
                   float x2, float y2, float z2, float dx2, float dy2, float dz2) {
	// ...
}

struct Point {
	// ...
};

// better:

bool doRaysCollide(Point start1, Point end1, Point start2, Point end2) {
	// ...
}

// even better:

struct Ray {
	Point origin;
	Point destination;
	// ...
};

bool doRaysCollide(Ray a, Ray b) {
	// ...
}

///////////////////////////////////////////////////////////////////////////////

int main() {

	// Terrible function design
	// -- no idea what this does just by looking at the invocation
	searchAndReplace("Hello World", "hello", "Goodbye", true, false, false, false);

	// a bit better
	searchAndReplace("Hello World", "hello", "Goodbye", ReplaceParameters::IGNORE_CASE);

	// much better
	searchAndReplaceFirst("Hello World", StringIgnoringCase("hello"), "Goodbye");

	return 0;
}

