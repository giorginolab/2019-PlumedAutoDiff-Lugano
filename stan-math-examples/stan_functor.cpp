/* Autodifferentation, take 2, using gradient and functors (more intuitive)?
 * See ./rev/mat/functor/gradient_test.cpp and https://arxiv.org/pdf/1509.07164.pdf
 */


#include <cmath>
#include <stan/math/rev/mat.hpp>
#include "run_and_time.hpp"



using Eigen::Matrix;
using Eigen::Dynamic;

using std::vector;






/* This struct functor thing baffles me, but the point is to implement operator() assuming
   an arbitrary number of parameters in the vector x . The trick is that instead of scalars
   you should assume to have type T. Eigen's methods are available. */
class curvature_fun {
public:
    template <typename T>
    T operator()(const Eigen::Matrix<T, Eigen::Dynamic, 1>& x)
    const {
        Matrix<T, 3, 1> a_, o_, b_;

        // Reshape for convenience
        a_ << x(0) , x(1) , x(2);
        o_ << x(3) , x(4) , x(5);
        b_ << x(6) , x(7) , x(8);

        Matrix<T, 3, 1> xx, yy, x_y;
        xx = a_-o_;
        yy = b_-o_;
        x_y = a_-b_;

        T cos2_a = pow(xx.dot(yy),2.0) / xx.dot(xx) / yy.dot(yy);
        T sin2_a = 1.0 - cos2_a;

        T radius2 = x_y.dot(x_y) / sin2_a / 4.0;
        T radius = sqrt(radius2);

        return(radius);
    }
};


void grad_curvature(Matrix<double,Dynamic,1> x, double &fx, Matrix<double,Dynamic,1> &grad_fx ) {
    curvature_fun f;
    // Matrix<double,Dynamic,1> x=xx;  // Where to evaluate f and grad f
    // double fx;                       // The value of f(x)
    // Matrix<double,Dynamic,1> grad_fx; // Value of grad f(x)
    stan::math::gradient(f,x,fx,grad_fx);
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

    stan::math::set_zero_all_adjoints();
}




int main(int argc, char ** argv) {
    run_and_time(test_curvature);
}

