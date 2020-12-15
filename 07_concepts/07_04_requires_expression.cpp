
// basic requires expression in a concept definition
template <typename T>
concept Addable = requires(T x) {
	x + x;
};

// this is a requires-clause, not requires-expression
template <typename T>
requires Addable<T> 
    T add(T a, T b) {
	return a + b;
}

// ad-hoc constraint, note keyword used twice
// first one starts a requires-clause, second a requires-expression
template <typename T>
requires requires(T x) {
	x + x;
} 
T add(T a, T b) {
	return a + b;
}
// this is very ugly, but to an extent at least it's intentionally
// and justifiably ugly:
// if you need a given set of constraints you should almost always
// have reason to give it a meaningful name, and likely reuse it


class stream;

// note that parameters introduced by the requires expression
// have *no storage, linkage or lifetime*. 
// They are constructs purely for compile-time type checking
template <typename T>
concept Streamable = requires(T x, stream s) {
	s << x;
};
