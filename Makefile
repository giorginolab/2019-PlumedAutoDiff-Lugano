# For stan 2.19.1 (the latest) use
STANMATH=$(HOME)/compile/stan-math
CPPFLAGS=-I$(STANMATH) -I$(STANMATH)/lib/eigen_3.3.3/ -I$(STANMATH)/lib/sundials_4.1.0/include -I$(STANMATH)/lib/boost_1.69.0

# Stan 2.17.1 used to use
# CPPFLAGS=-I$(STANMATH) -I$(STANMATH)/lib/eigen_3.3.3/ -I$(STANMATH)/lib/cvodes_2.9.0/include -I$(STANMATH)/lib/boost_1.64.0


# Using clang because it's faster once you precompile the header. GCC works well too, if 
# you disable the precompiled header. To do so, undefine USE_PCH below..

USE_PCH = -include $(PCH:.pch=)

CXX = clang++
CXXFLAGS_MAKEPCH = -O -Wall  -g -std=c++14 
CXXFLAGS = $(USE_PCH) $(CXXFLAGS_MAKEPCH)
LOADLIBES = -lm

ifdef USE_PCH
  PCH = /var/tmp/stan-math.hpp.pch

default_with_pch: $(PCH) default 

# Precompile the library as a header. The file is large, so keep it in a temporary directory.
$(PCH):
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_MAKEPCH) -x c++-header  $(STANMATH)/stan/math/rev/mat.hpp -o $@

endif


EXES:=stan_lambda stan_functor stan_native stan_sandbox stan_iterative stan_perf_minimal

default: $(EXES)

clean:
	-rm $(EXES) *.o


# clang++ -x c++-header -O -std=c++14 -I/home/toni/compile/stan-math -I/home/toni/compile/stan-math/lib/eigen_3.3.3/ -I/home/toni/compile/stan-math/lib/sundials_4.1.0/include -I/home/toni/compile/stan-math/lib/boost_1.69.0  ~/compile/stan-math/stan/math/rev/mat.hpp -o mat.hpp.pch
