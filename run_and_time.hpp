#include <ctime>
    
void timeit(void (*f)(bool) , unsigned int howmany) {
    clock_t begin=std::clock();

    for (int i=0; i<howmany; i++) {
	f(false);
        stan::math::set_zero_all_adjoints();
    }
    
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    printf ("Timed as %.2lf μs/call.\n", elapsed_secs * 1.0e6 / howmany );
}



const unsigned int howmany_default=1e6;

void run_and_time(void (*f)(bool) , unsigned int howmany = howmany_default) {
    f(true);			// run
    timeit(f, howmany);			// time
}

