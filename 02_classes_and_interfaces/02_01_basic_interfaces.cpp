
// Some examples are taken (or minimally adapted) from the C++ Core Guidelines

#include <cmath>

// PARAMETER TYPES ////////////////////////////////////////////////////////////

/// Bad example: use global state to affect behavior

bool g_round_up = false;

int round_bad(double d) {
	return (int)((g_round_up) ? ceil(d) : d); // don't: "invisible" dependency
}

/// Better solution

int round_better(double d, bool round_up) {
	return (int)((round_up) ? ceil(d) : d);
}

// PRECISELY TYPED ////////////////////////////////////////////////////////////

/// Bad example: unclear semantics

void sleep(double duration) {
	// What is "duration"?
	// If I call sleep(1.0) will it sleep for a second or a millisecond?
	// ...
}

/// Better solution: use specific type

#include <chrono>

void sleep(std::chrono::milliseconds duration) {
	// Semantics are clear just from looking at the type
	// ...
}

///////////////////////////////////////////////////////////////////////////////

int main() {

	/// Note: in modern C++, more precisely typed interfaces
	/// does not necessarily mean that they are more cumbersome to use

	using namespace std::chrono_literals;

	sleep(33ms);

	return 0;
}

