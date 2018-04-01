test : simple_int_set.o simple_int_set_main.o
	g++ -o test simple_int_set.o simple_int_set_main.o -Wall -g

simple_int_set.o : simple_int_set.cc
	g++ -c -o simple_int_set.o simple_int_set.cc

simple_int_set_main.o : simple_int_set_main.cc
	g++ -c -o simple_int_set_main.o simple_int_set_main.cc

clean :
	rm *.o test
