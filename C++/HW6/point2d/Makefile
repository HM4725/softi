test : point2d.o point2d_main.o
	g++ -o test point2d.o point2d_main.o

point2d.o : point2d.cc
	g++ -c -o point2d.o point2d.cc

point2d_main.o : point2d_main.cc
	g++ -c -o point2d_main.o point2d_main.cc -std=c++11	-Wall -g

clean:
	rm *.o test
