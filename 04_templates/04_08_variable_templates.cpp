
// variable template for pi

template<class T>
constexpr T pi = T(3.1415926535897932385L);

template<class T>
T circular_area(T r) // function template
{
	return pi<T> * r * r; // pi<T> is a variable template instantiation
}

// example from variable templates proposal (N3651)
