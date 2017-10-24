#include <string>

using std::string;

/// PARAMETER TYPES ///////////////////////////////////////////////////////////

string searchAndReplaceFirst(string in, string toReplace, string replacement) { }

// strings might be larger and not cheap to copy
// - move semantics help in some case, but not all

/// *BAD* alternative: /////

string searchAndReplaceFirstBAD(string& in, string& toReplace, string& replacement) { }

// no copies, but we might inadvertently change one of the input strings!!
// also: whoever is using our interface will think that we want to change these strings
// and: it doesn't even work for a common use case! (see below)

/// Best choice: /////

string searchAndReplaceFirstBEST(const string& in,
	                             const string& toReplace, const string& replacement) { }

// a *constant reference* allows us to avoid any overhead for copies,
// but prevents changing the underlying object
// Note: a constant lvalue reference can also bind to rvalues -- why?

/// In-out parameters: //////

// what if we actually *do* want to change a parameter?

void searchAndReplaceFirstInPlace(string& inout, const string& toReplace, const string& replacement) {}

// this is the correct time to use a non-const reference

//////////////////////////////////////////////////////////////////////////////

int main() {

	searchAndReplaceFirstBAD("Bla", "a", "b");

	searchAndReplaceFirstBEST("Bla", "a", "b");

	return 0;
}

