#include <cmath>
#include <stan/math/rev/mat.hpp>


#include "run_and_time.hpp"

using std::vector;

using stan::math::var;
using stan::math::vector_d;
using stan::math::vector_v;






void test_curvature(bool print=true)
{
    double dt=2*M_PI/30;
    double r=2.5;

    vector_v a(3), o(3), b(3);
    a << r ,          0 ,           0;
    o << r*cos(dt),   r*sin(dt),    0 ;
    b << r*cos(2*dt), r*sin(2*dt),  0;

    vector_v x = a-o;
    vector_v y = b-o;

    var cos2_a = pow(dot_product(x,y),2.0) / dot_self(x) / dot_self(y);
    var sin2_a = 1.0 - cos2_a;

    vector_v x_y = subtract(a,b);
    var radius2 =  dot_self(x_y) / sin2_a / 4.0;
    var radius = sqrt(radius2);

    radius.grad();

    if(print) {
	std::cout << "Radius: " << radius.val() << std::endl;
	
        for (int i=0; i<3; i++) std::cout << a[i].adj() << " ";
        std::cout << std::endl;
        for (int i=0; i<3; i++) std::cout << o[i].adj() << " ";
        std::cout << std::endl;
        for (int i=0; i<3; i++) std::cout << b[i].adj() << " ";
        std::cout << std::endl;
    }

    stan::math::set_zero_all_adjoints();
    stan::math::recover_memory();

}





int main(int argc, char ** argv)
{
    run_and_time(test_curvature,atoi(argv[1]));
}

