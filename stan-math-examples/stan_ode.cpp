/* Autodifferentation, take 2, using gradient and functors (more intuitive)?
 * See ./rev/mat/functor/gradient_test.cpp and https://arxiv.org/pdf/1509.07164.pdf
 */



#include <cmath>
#include <time.h>

#include <stan/math.hpp>

#include <stan/math/rev/arr.hpp>
#include <stan/math/rev/mat.hpp>
#include <stan/math/rev/mat/functor/gradient.hpp>

#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>





using std::vector;
using namespace stan::math;



class sho_functor {
 public:
  template <typename T0, typename T1, typename T2>
  inline std::vector<typename stan::return_type<T1, T2>::type>
  // time
  // state
  // parameters
  // double data
  // integer data
  operator()(const T0& t_in, const std::vector<T1>& y_in,
             const std::vector<T2>& theta, const std::vector<double>& x,
             const std::vector<int>& x_int, std::ostream* msgs) const {
    if (y_in.size() != 2)
      throw std::domain_error("Functor called with inconsistent state");

    std::vector<typename stan::return_type<T1, T2>::type> f;
    f.push_back(y_in.at(1));
    f.push_back(-theta.at(0) * theta.at(0) * y_in.at(0));

    return f;
  }
};

class test_functor_double_var_2 {
 public:
  template <typename T>
  inline T operator()(Eigen::Matrix<T, Eigen::Dynamic, 1>& x) const {
    sho_functor sho;

    std::vector<T> theta;
    theta.push_back(4.0);

    std::vector<T> y0;
    y0.push_back(0.0);
    y0.push_back(1.0);

    double t0 = 0.0;
    std::vector<double> ts;
    for (double t=t0; t<tmax; t+=0.1) {
	ts.push_back(t);
    }

    std::vector<double> data;
    std::vector<int> data_int;

    std::vector<std::vector<T> > ys = stan::math::integrate_ode_rk45(
        sho, y0, t0, ts, theta, data, data_int, 0);

    for(int i=0; i<ts.size(); i++) {
	printf("y1(%.2lf) = %.2lf\n",ts.at(i),ys.at(1).at(i));
	printf("y2(%.2lf) = %.2lf\n",ts.at(i),ys.at(2).at(i));
    }
  }
};



int main(int argc, char ** argv) {
    
}
