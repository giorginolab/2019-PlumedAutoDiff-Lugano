
STANMATH=$(HOME)/compile/stan-math
CPPFLAGS=-I$(STANMATH) -I$(STANMATH)/lib/eigen_3.3.3/ -I$(STANMATH)/lib/sundials_4.1.0/include -I$(STANMATH)/lib/boost_1.69.0

# Stan 2.17.1 used
# CPPFLAGS=-I$(STANMATH) -I$(STANMATH)/lib/eigen_3.3.3/ -I$(STANMATH)/lib/cvodes_2.9.0/include -I$(STANMATH)/lib/boost_1.64.0

CXX=clang++
CXXFLAGS=-O -Wall  -g -std=c++14 -include /tmp/mat.hpp
LOADLIBES=-lm

EXE:=stan_lambda stan_functor stan_native stan_sandbox stan_iterative stan_perf_minimal

default: $(EXE)


clean:
	-rm $(EXE) *.o

/tmp/mat.hpp.pch:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -x c++-header $(STANMATH)/stan/math/rev/mat.hpp -o $@

# clang++ -x c++-header -O -std=c++14 -I/home/toni/compile/stan-math -I/home/toni/compile/stan-math/lib/eigen_3.3.3/ -I/home/toni/compile/stan-math/lib/sundials_4.1.0/include -I/home/toni/compile/stan-math/lib/boost_1.69.0  ~/compile/stan-math/stan/math/rev/mat.hpp -o mat.hpp.pch
