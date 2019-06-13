
STANMATH=$(HOME)/compile/stan-math
CPPFLAGS=-I$(STANMATH) -I$(STANMATH)/lib/eigen_3.3.3/ -I$(STANMATH)/lib/sundials_4.1.0/include -I$(STANMATH)/lib/boost_1.69.0 
CXX=clang++
CXXFLAGS=-O -Wall  -g -std=c++14
LOADLIBES=-lm

EXE:=stan_lambda stan_easy stan_manual stan_sandbox stan_iterative

default: $(EXE)


clean:
	-rm $(EXE) *.o
