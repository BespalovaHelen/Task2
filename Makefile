CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

all: test

matrix.o: matrix.cpp matrix.h
	$(CXX) $(CXXFLAGS) -c matrix.cpp -o matrix.o

main.o: main.cpp matrix.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

test: matrix.o main.o
	$(CXX) matrix.o main.o -o test
	./test

clean:
	rm -f *.o test

.PHONY: all test clean
