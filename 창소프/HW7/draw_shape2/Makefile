test: draw_shape2.o draw_shape_main2.o
	g++ -o test draw_shape2.o draw_shape_main2.o
draw_shape2.o: draw_shape2.cc
	g++ -c -o draw_shape2.o draw_shape2.cc -Wall -g -std=c++11
draw_shape_main2.o: draw_shape_main2.cc
	g++ -c -o draw_shape_main2.o draw_shape_main2.cc -Wall -g -std=c++11
clean:
	rm *.o test

