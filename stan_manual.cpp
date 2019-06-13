#include <cmath>
// #include <stan/math.hpp>
// #include <stan/math/mix/scal.hpp>
#include <stan/math/rev/mat.hpp>
#include <vector>

#include <time.h>
const int MAX_CALLS=1e6;


using std::vector;

using stan::math::var;
using stan::math::vector_d;
using stan::math::vector_v;



// Assuming vectors of the right size. This is probably wrong - too slow.
var curvature(vector<double> &a, vector<double> &o, vector<double> &b, bool print=true)
{
    vector_v a_(3); a_ << a[0], a[1], a[2];
    vector_v o_(3); o_ << o[0], o[1], o[2];
    vector_v b_(3); b_ << b[0], b[1], b[2];

    vector_v x = a_-o_;
    vector_v y = b_-o_;

    var cos2_a = pow(dot_product(x,y),2.0) / dot_self(x) / dot_self(y);
    var sin2_a = 1.0 - cos2_a;

    vector_v x_y = subtract(a_,b_);
    var radius2 =  dot_self(x_y) / sin2_a / 4.0;
    var radius = sqrt(radius2);

    vector<double> ga, go, gb;
    radius.grad();

    if(print) {
        for (int i=0; i<3; i++) std::cout << a_[i].adj() << " ";
        std::cout << std::endl;
        for (int i=0; i<3; i++) std::cout << o_[i].adj() << " ";
        std::cout << std::endl;
        for (int i=0; i<3; i++) std::cout << b_[i].adj() << " ";
        std::cout << std::endl;
    }

    return(radius);
}




void test_curvature()
{
    double dt=2*M_PI/30;
    double r=2.5;

    vector<double> a(3), b(3), c(3);
    a = { r , 0 , 0};
    b = { r*cos(dt), r*sin(dt), 0 };
    c = {r*cos(2*dt), r*sin(2*dt), 0};

    var radius = curvature(a,b,c);
    std::cout << "Radius: " << radius.val() << std::endl;

}




void timeit()
{
    double dt=2*M_PI/30;
    double r=2.5;

    vector<double> a(3), b(3), c(3);
    a = { r , 0 , 0};
    b = { r*cos(dt), r*sin(dt), 0 };
    c = {r*cos(2*dt), r*sin(2*dt), 0};

    clock_t t=clock();
    double crap=0.;

    for (int i=0; i<MAX_CALLS; i++) {
         curvature(a,b,c,false);
        stan::math::recover_memory();
    }

    t=clock()-t;
    printf ("It took me %f seconds (%f μs/call) \n %f.\n",
            ((float)t)/CLOCKS_PER_SEC,
            1.0e6*((float)t)/CLOCKS_PER_SEC/MAX_CALLS,crap);

}

int main(int argc, char ** argv)
{
    test_curvature();
    timeit();
}