/* 
 * Test autodifferentiation of a function computed via an iterative
 * algorithm (Newton's method). 
 */


#include <cmath>
#include <stan/math/rev/mat.hpp>
#include <time.h>

using Eigen::Matrix;
using Eigen::Dynamic;

using std::vector;

/*
 * Test autodifferentiation of a function computed via an iterative
 * algorithm (Newton's method). Function input: B, C. Function output:
 * a solution to the x**2 + 2*B*x + C == 0 equation. Could be any
 * equation, but this was chosen because the gradient can be
 * hand-checked.

    B=-3  C=1  -->
		  sol1              sol2
    x      0.171572875253810   5.82842712474619        3 +- 2√2

    dx/db  0.0606601717798213 -2.06066017177982       -1 +- 3√2/4
    dx/dc  0.176776695296637  -0.176776695296637      +- √2/8
    
    The output should converge to one of the two columns, and it does.

*/

struct newton {
private:
  double p;			// unused
  double convergence = 1e-6;
  int max_iter = 1000;
public:
  newton(double p): p(p) {}
  
  template <typename T>
  T operator()(const Eigen::Matrix<T, Eigen::Dynamic, 1>& bc) const {
    T x=1.0;			// note 1a
    int i=0;

    T b=bc(0);
    T c=bc(1);

    // Iteratively solve  x**2 + 2*B*x + C
    while(i++ < max_iter) {
      T dx = (x*x + 2*b*x + c)/(2*x+2*b); 
      x -= dx;			// note 1b
      if( abs(dx)<convergence) break; // 1c
    }

    std::cout << "Converged in " << i << std::endl;
    return(x);
  }
};

/* note 1. tricky! One would think that 1b and 1c can be
   interchanged. Almost so!  if they are exchanged, AND the solution
   happens to be EXACTLY the starting guess, x would never be
   written, and the gradient would be incorrectly 0 0 !
*/


void test() {
    using namespace std;
  
    // Input. B and C are entered on stdin
    const int n=2;
    Matrix<double,n,1> bc;
    cout << "Enter " << n << " values" << endl;
    int i=0;
    while(i<n) 
      cin >> bc(i++); 

    cout << "Entered: " << bc << endl;

    // F to be derived
    newton f(42.0);		// unused parameter

    // Output
    double fx;
    Matrix<double,Dynamic,1> grad_fx;

    stan::math::gradient(f,bc,fx,grad_fx);

    cout << "Returns: " << fx << endl;
    cout << "Gradient: " << endl << grad_fx << endl;

    double B=bc(0), C=bc(1);
    double det=sqrt( pow(B,2)-C);
    
    cout << "Expected: " << -B+det << " [" << -1+B/det << " " << -1./2/det << "]" << endl;
    cout << "      or: " << -B-det << " [" << -1-B/det << " " <<  1./2/det << "]" << endl;
    

    stan::math::set_zero_all_adjoints();
}




int main(int argc, char ** argv) {
    test();
}
