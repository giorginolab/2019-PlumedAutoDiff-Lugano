# Location where you extracted the stan math library, https://github.com/stan-dev/math
STANMATH=$(HOME)/compile/stan-math

# For stan 2.19.1 (the latest) use
CPPFLAGS=-I$(STANMATH) -I$(STANMATH)/lib/eigen_3.3.3/ -I$(STANMATH)/lib/sundials_4.1.0/include -I$(STANMATH)/lib/boost_1.69.0

# Stan 2.17.1 used to use
# CPPFLAGS=-I$(STANMATH) -I$(STANMATH)/lib/eigen_3.3.3/ -I$(STANMATH)/lib/cvodes_2.9.0/include -I$(STANMATH)/lib/boost_1.64.0


# Compiling the library is a bit slow. Clang's precompiled headers speed it up considerably. 
# To disable the precompiled header, undefine USE_PCH below.
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
	$(CXX) $(CXXFLAGS_MAKEPCH) $(CPPFLAGS)  -x c++-header  $(STANMATH)/stan/math/rev/mat.hpp -o $@
endif


EXES:=stan_ode stan_lambda stan_functor stan_native stan_sandbox stan_iterative stan_perf_minimal

default: $(EXES)

clean:
	-rm $(EXES) *.o


# clang++ -x c++-header -O -std=c++14 -I/home/toni/compile/stan-math -I/home/toni/compile/stan-math/lib/eigen_3.3.3/ -I/home/toni/compile/stan-math/lib/sundials_4.1.0/include -I/home/toni/compile/stan-math/lib/boost_1.69.0  ~/compile/stan-math/stan/math/rev/mat.hpp -o mat.hpp.pch
