#include <iostream>

#include <Eigen/Dense>
using namespace Eigen;

int main() {

	// simple arithmetic

	Matrix2d a;
	a << 1, 2,
	     3, 4;
	MatrixXd b(2, 2);
	b << 2, 3,
	     1, 4;
	std::cout << "a + b =\n" << a + b << std::endl;
	std::cout << "a - b =\n" << a - b << std::endl;

	Vector3d v(1, 2, 3);
	Vector3d w(1, 0, 0);
	std::cout << std::endl << "-v + w - v =\n" << -v + w - v << std::endl;


	// row / column operations

	Matrix3d m;
	m << 1, 2, 3,
	     4, 5, 6,
	     7, 8, 9;
	double alpha = 0.5;
	double beta = 2.0;
	std::cout << std::endl << "m1\n" << m << std::endl;;

	m.row(0) += alpha * m.row(1);
	std::cout << std::endl << "m2\n" << m << std::endl;;

	m.col(1) = alpha * m.col(2) + beta * m.col(0);
	std::cout << std::endl << "m3\n" << m << std::endl;;

	m.col(2).swap(m.col(1));
	std::cout << std::endl << "m4\n" << m << std::endl;;
}
