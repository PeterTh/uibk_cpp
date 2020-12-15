#include <utility>
#include <concepts>

// Simple Requirements
// -------------------

template <typename T>
concept Addable = requires(T a, T b) {
	a + b; // "the expression a+b is a valid expression that will compile"
};

template <class T, class U = T>
concept Swappable = requires(T&& t, U&& u) {
	std::swap(std::forward<T>(t), std::forward<U>(u));
	std::swap(std::forward<U>(u), std::forward<T>(t));
};

// Type Requirements
// -----------------

template <typename T>
using Ref = T&;

template<class T>
struct S {};

template <typename T>
concept TypeRequirements = requires {
	typename T::inner; // required nested member name
	typename S<T>;     // required class template specialization
	typename Ref<T>;   // required alias template substitution
};

// Compound Requirements
// ---------------------

template <typename T>
concept CompoundRequirements = requires(T x) {
	{ *x } -> std::convertible_to<typename T::inner>; 
		// the expression *x must be valid
	    // AND the type T::inner must be valid
	    // AND the result of *x must be convertible to T::inner

	{ x + 1 } -> std::same_as<int>; 
		// the expression x + 1 must be valid
		// AND std::same_as<decltype((x + 1)), int> must be satisfied
		// i.e., (x + 1) must be a prvalue of type int

	{ x * 1 } noexcept -> std::convertible_to<T>; 
		// the expression x * 1 must be valid
		// AND x * 1 must not be potentially throwing
		// AND its result must be convertible to T
};

// Nested Requirements
// -------------------

template <class T>
concept Semiregular = 
		   std::default_initializable<T> && std::copy_constructible<T> && std::destructible<T> 
		&& requires(T a, std::size_t n) {
	requires std::same_as<T*, decltype(&a)>;       // nested: "Same<...> evaluates to true"
	{ a.~T() } noexcept;                           // compound: "a.~T()" is a valid expression that doesn't throw
	requires std::same_as<T*, decltype(new T)>;    // nested: "Same<...> evaluates to true"
	requires std::same_as<T*, decltype(new T[n])>; // nested
	{delete new T};                                // compound
	{delete new T[n]};                             // compound
};
