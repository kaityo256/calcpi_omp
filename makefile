all: icpc.out gcc.out

CC=icpc
CPPFLAGS=-qopenmp -std=c++11 -O3

icpc.out: calcpi_omp.cpp
	icpc -qopenmp -std=c++11 -O3 $< -o $@

gcc.out: calcpi_omp.cpp
	g++ -fopenmp -std=c++11 -O3 $< -o $@

clean:
	rm -f icpc.out gcc.out
