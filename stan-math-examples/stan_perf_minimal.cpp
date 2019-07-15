#include <stan/math/rev/mat.hpp>


using std::vector;

using stan::math::var;
using stan::math::vector_v;


void test(bool print=true)
{
    vector_v x(3);
    x << 1 ,          0 ,           0;

    var y = dot_self(x);
    y.grad();

    if(print) {
	std::cout << "y: " << y.val() << std::endl;
	for (int i=0; i<3; i++) std::cout << x[i].adj() << " ";
        std::cout << std::endl;
    }

    stan::math::set_zero_all_adjoints();
    stan::math::recover_memory();
}



int main(int argc, char ** argv)
{
    test();
    for(int i=0; i<atoi(argv[1]); i++)
	test(false);
    test();
}

