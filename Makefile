all: main.o 
	c++ -std=c++11 -g main.o -o main
main.o: main.cpp matrix.h
	c++ -std=c++11 -c -g main.cpp
clean:
	rm *.o main
