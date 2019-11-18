#include <string>
#include <vector>
#include <limits>
#include <iostream>

using std::string;

/// PARAMETER TYPES ///////////////////////////////////////////////////////////

string searchAndReplaceFirst(string in, string toReplace, string replacement);

// strings might be larger and not cheap to copy
// - move semantics help in some case, but not all

/// *BAD* alternative: /////

string searchAndReplaceFirstBAD(string& in, string& toReplace, string& replacement);

// no copies, but we might inadvertently change one of the input strings!!
// also: whoever is using our interface will think that we want to change these strings
// and: it doesn't even work for a common use case! (see below)

/// Best choice: /////

string searchAndReplaceFirstBEST(const string& in,
                                 const string& toReplace, const string& replacement);

// a *constant reference* allows us to avoid any overhead for copies,
// but prevents changing the underlying object
// Note: a constant lvalue reference can also bind to rvalues -- why?

/// In-out parameters: //////

// what if we actually *do* want to change a parameter?

void searchAndReplaceFirstInPlace(string& inout, const string& toReplace, const string& replacement);

// this is the correct time to use a non-const reference

//////////////////////////////////////////////////////////////////////////////

void usage() {
	searchAndReplaceFirstBAD("Bla", "a", "b");

	searchAndReplaceFirstBEST("Bla", "a", "b");
}

/// MULTIPLE RETURN VALUES ///////////////////////////////////////////////////////////

// Example: min/max

// Old/C-style

void minmax_c(const std::vector<int>& input, int& min, int& max) {
    min = std::numeric_limits<int>::max();
    max = std::numeric_limits<int>::min();
    for(auto& val : input) {
        if(val < min) min = val;
        if(val > max) max = val;
    }
}

// Multiple return values using pair

std::pair<int,int> minmax_p(const std::vector<int>& input) {
    std::pair<int,int> ret = { std::numeric_limits<int>::max(), std::numeric_limits<int>::min() };
    for(auto& val : input) {
        if(val < ret.first) ret.first = val;
        if(val > ret.second) ret.second = val;
    }
    return ret;
}

// Multiple return values using struct

struct Bounds {
    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();
};

Bounds minmax_s(const std::vector<int>& input) {
    Bounds ret;
    for(auto& val : input) {
        if(val < ret.min) ret.min = val;
        if(val > ret.max) ret.max = val;
    }
    return ret;
}

// Usage

int main() {

    std::vector<int> items { -4, 1, 22, -15, 50, 0, 3};

    { // use minmax_c
        int min = 0, max = 0;
        minmax_c(items, min, max);
        std::cout << "minmax_c: " << min << " " << max << std::endl;
    }

    { // use minmax_p
        auto [min,max] = minmax_p(items);
        std::cout << "minmax_p: " << min << " " << max << std::endl;
    }

    { // use minmax_s
        auto [min,max] = minmax_s(items);
        std::cout << "minmax_s: " << min << " " << max << std::endl;
    }
}
