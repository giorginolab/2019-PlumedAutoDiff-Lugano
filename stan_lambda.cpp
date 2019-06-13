/* Autodifferentation, take 2, using gradient and functors (more intuitive)?
 * See ./rev/mat/functor/gradient_test.cpp and https://arxiv.org/pdf/1509.07164.pdf
 */


#include <cmath>
#include <stan/math/rev/mat.hpp>
#include <time.h>
#include <type_traits>

const int MAX_CALLS=1e7;


using Eigen::Matrix;
using Eigen::Dynamic;

using std::vector;






/* This struct functor thing baffles me, but the point is to implement operator() assuming
   an arbitrary number of parameters in the vector x . The trick is that instead of scalars
   you should assume to have type T. Eigen's methods are available. */
auto curvature_lambda = [] (auto x) {

    // std::remove_reference<decltype(x)> a_, o_, b_;
    decltype(x) a_, o_, b_;
    a_.resize(3,1);
    o_.resize(3,1);
    b_.resize(3,1);

    // Reshape for convenience
    a_ << x(0) , x(1) , x(2);
    o_ << x(3) , x(4) , x(5);
    b_ << x(6) , x(7) , x(8);

    decltype(x) xx, yy, x_y;
    xx.resize(3,1);
    yy.resize(3,1);
    x_y.resize(3,1);

    xx = a_-o_;
    yy = b_-o_;
    x_y = a_-b_;

    auto cos2_a = pow(xx.dot(yy),2.0) / xx.dot(xx) / yy.dot(yy);
    auto sin2_a = 1.0 - cos2_a;

    auto radius2 = x_y.dot(x_y) / sin2_a / 4.0;
    auto radius = sqrt(radius2);

    return(radius);
};





void grad_curvature(Matrix<double,Dynamic,1> x, double &fx, Matrix<double,Dynamic,1> &grad_fx ) {
    // curvature_class f;
    // Matrix<double,Dynamic,1> x=xx;  // Where to evaluate f and grad f
    // double fx;                       // The value of f(x)
    // Matrix<double,Dynamic,1> grad_fx; // Value of grad f(x)
    stan::math::gradient(curvature_lambda,x,fx,grad_fx);
}


void test_curvature() {
    double dt=2*M_PI/30;
    double r=2.5;

    Matrix<double,9,1> x;
    x << r , 0 , 0 ,
    r*cos(dt), r*sin(dt), 0,
    r*cos(2*dt), r*sin(2*dt), 0;

    double radius;
    Matrix<double,Dynamic,1> grad_fx;

    grad_curvature(x,radius,grad_fx);
    std::cout << "Radius: " << radius << std::endl;

    std::cout << grad_fx << std::endl;

}



void timeit() {
    double dt=2*M_PI/30;
    double r=2.5;

    Matrix<double,9,1> x;
    x << r , 0 , 0 ,
    r*cos(dt), r*sin(dt), 0,
    r*cos(2*dt), r*sin(2*dt), 0;

    double radius;
    Matrix<double,Dynamic,1> grad_fx;

    double crap=0;

    clock_t t=clock();

    for (int i=0; i<MAX_CALLS; i++) {
        grad_curvature(x,radius,grad_fx);
        stan::math::set_zero_all_adjoints();
    }

    t=clock()-t;

    printf ("It took me %f seconds (%f μs/call) \n %f.\n",
            ((float)t)/CLOCKS_PER_SEC,
            1.0e6*((float)t)/CLOCKS_PER_SEC/MAX_CALLS,crap);

}




int main(int argc, char ** argv) {
    test_curvature();
    timeit();
}
