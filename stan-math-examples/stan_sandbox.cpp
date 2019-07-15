/* Autodifferentation, take 2, using gradient and functors (more intuitive)?
 * See ./rev/mat/functor/gradient_test.cpp and https://arxiv.org/pdf/1509.07164.pdf
 */


#include <cmath>
#include <stan/math/rev/mat.hpp>
#include <time.h>
const int MAX_CALLS=1e7;


using Eigen::Matrix;
using Eigen::Dynamic;

using std::vector;



/* Implementing functors may seem baffling, but the point is to
   implement operator() assuming an arbitrary number of parameters in
   the vector x . The trick is that instead of scalars you should
   assume to have type T. Eigen's methods are available. */
struct fun1 {
    template <typename T>
    T operator()(const Eigen::Matrix<T, Eigen::Dynamic, 1>& x)
    const {
	T ret=1.0;
	T p=x(1);

	while(p>0.0) {
	    ret *= x(0);
	    p -= 1.0;
	}

        return(ret);
    }
};


/* This is more correct: do not differentiate against p (if you don't
 * want to) */
struct fun2 {
    fun2(int p): p(p) {}
    template <typename T>
    T operator()(const Eigen::Matrix<T, Eigen::Dynamic, 1>& x)
	const {
	T ret=1.0;
	int pp = p;

	while(pp>0) {
	    ret *= x(0);
	    pp--;
	}

        return(ret);
    }
private:
    int p;
};


struct power_fun {
  power_fun(double exp_): exp_(exp_) {}

  template <typename T>
  T operator()(const Eigen::Matrix<T, Eigen::Dynamic, 1>& x) const {
    T ret;
    ret=pow(x(0),exp_);
    return(ret);
  }
private:
  double exp_;
};



void test() {
    const int n=2;

    double po;
    scanf("%lf",&po);
    
    power_fun f(po);
    Matrix<double,n,1> x;
    double fx;
    Matrix<double,Dynamic,1> grad_fx;

    // Input
    std::cout << "Enter " << n << " values" << std::endl;
    for (int i=0; i<n; i++) {
	double u;
	scanf("%lf",&u);
	x(i)=u;
    }

    std::cout << "Entered: " << x << std::endl;
    
    // Output
    stan::math::gradient(f,x,fx,grad_fx);

    std::cout << "Returns: " << fx << std::endl;
    std::cout << "Gradient: " << grad_fx << std::endl;

    stan::math::set_zero_all_adjoints();
}




int main(int argc, char ** argv) {
    test();
}
