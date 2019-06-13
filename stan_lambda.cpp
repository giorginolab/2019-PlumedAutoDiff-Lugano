/* Autodifferentation, take 2, using gradient and functors (more intuitive)?
 * See ./rev/mat/functor/gradient_test.cpp and https://arxiv.org/pdf/1509.07164.pdf
 */


#include <cmath>
#include <stan/math/rev/mat.hpp>
#include "run_and_time.hpp"


using Eigen::Matrix;
using Eigen::Dynamic;

using std::vector;




//  This is the function computing the gradient. 
void grad_curvature(Matrix<double,Dynamic,1> x, double &fx, Matrix<double,Dynamic,1> &grad_fx ) {

    bool inverse=false;

    
    // This is the function is differentiated against all elements of
    // the argument x, which is a const Matrix<T, Dynamic, 1>& . Pass
    // parameters (not being differentiated against) with the square
    // brackets. 
    auto curvature_lambda = [inverse] (auto x) {
	typedef typename decltype(x)::Scalar T;

	/* We may need to extract the type T (e.g. if we want to make
	   compatible Eigen objects). Otherwise "auto" may just do
	   it. */

	// Reshape for convenience
	typedef Matrix<T, 3, 1> T3;
	T3 a_, o_, b_;
	a_ << x(0) , x(1) , x(2);
	o_ << x(3) , x(4) , x(5);
	b_ << x(6) , x(7) , x(8);
	
	// "auto xx=..." also works, but it's slower in this case.
	T3 xx = a_-o_;
	T3 yy = b_-o_;
	T3 x_y = a_-b_;

	// "T cos2_a" also works. It's here for illustration
	auto cos2_a = pow(xx.dot(yy),2.0) / xx.dot(xx) / yy.dot(yy);
	auto sin2_a = 1.0 - cos2_a;

	auto radius2 = x_y.dot(x_y) / sin2_a / 4.0;
	auto radius = sqrt(radius2);

	return(inverse? 1.0/radius : radius);
    };


    // Perform the actual gradient computation. Arguments:
    //   a lambda function, see above         // Function to differentiate
    //   Matrix<double,Dynamic,1> x;          // Where to evaluate f and grad f
    //   double & fx;                         // The value of f(x), returned
    //   Matrix<double,Dynamic,1> & grad_fx;  // Value of grad f(x), returned
    stan::math::gradient(curvature_lambda,x,fx,grad_fx);
}


void test_curvature(bool print=true) {
    double dt=2*M_PI/30;
    double r=2.5;

    Matrix<double,9,1> x;
    x << r          , 0          , 0 ,
         r*cos(dt)  , r*sin(dt)  , 0 ,
	 r*cos(2*dt), r*sin(2*dt), 0 ;

    double radius;
    Matrix<double,Dynamic,1> grad_fx;
    grad_curvature(x,radius,grad_fx);

    if(print) {
	std::cout << "Radius: " << radius << std::endl;
	std::cout << grad_fx << std::endl;
    }
}





int main(int argc, char ** argv) {
    run_and_time(test_curvature);
}
