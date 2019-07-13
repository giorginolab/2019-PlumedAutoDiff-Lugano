Stan Math automatic differentiation examples
=============================

We demonstrate (and time) the use of the Stan Math library for
"realistic" CV differentiation problems. This code accompanies the talk
at CECAM's *Open source software for enhanced-sampling simulations*
https://www.cecam.org/workshop1749/ taking place on 25-27 July 2019 at
Università della Svizzera italiana, Lugano.

Preliminarly, you will need to

1. download and extract the Stan Math library from https://github.com/stan-dev/math 
2. edit the `STAN_HOME` variable in the `Makefile` accordingly


The files are sorted in a "didactical" order. Understanding the first
is sufficient for practical purposes.

All files must be invoked with an integer argument, the number of
repetitions for benchmarking purposes.

If you find this work useful,
please cite 
> T. Giorgino, How to differentiate collective variables in free energy codes: Computer-algebra code generation and automatic differentiation, Computer Physics Communications 228, 258–263 (2018) [doi](http://dx.doi.org/10.1016/j.cpc.2018.02.017) [arxiv](https://arxiv.org/abs/1709.06780) [plumID:19.011](https://www.plumed-nest.org/eggs/19/011/)


Basic example: `stan_lambda`
--------------------

Compute the radius of a circle passing through three points and its
gradient with respect to the three coordinates. The differentiand is
defined using a C++14 "lambda" with a 9x1 input (the coordinates, in
order `x1 y1 z1 x2 y2 z2 x3 y3 z3`) and a boolean parameter (`invert`,
whether to return the reciprocal of the result).

A call to `stan::math::gradient` with the arguments indicated in the
source performs the reverse-mode automatic differentiation and returns
simultaneously the outputs `fx` (the value of the function at the
requested point `x`) and `grad_fx` (its gradient, an Eigen
`Matrix<double, 9, 1>`).

Notes:

* The input must be a 1D vector, not a matrix, for `stan::math::gradient` to work.
* Vectors are `typedef` with convenient types of the [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) library.
* Eigen enables a number of vector operations, such as `.dot()`.
* `auto` types are also used for readability.


Older C++ syntax: `stan_functor`
--------------------

Like the above, but uses the "functor" syntax instead of lambda.


Differentiating through iterations: `stan_iterative`
--------------------

It is possible to differentiate results coming from (almost) arbitrary
algorithms. Here, for the sake of illustration, we solve the second-order
equation, `A x^2 + B x + C = 0`, by Newton's method. Iterations quickly
converge towards a solution `x` (if there is any). The derivative of the
solution with respect to A, B and C are computed via Stan, and
compared with the know exact values.


Low-level approach: `stan_native`
--------------------

Shows a more low-level approach where the variables being
differentiated are explicitly declared of `var` type;
the Eigen library is not used.


Other
--------------------

* `stan_perf_minimal.cpp`: minimal benchmark
* `stan_sandbox.cpp`: minimal harness for quick testing
* `run_and_time.hpp`: as the name implies


