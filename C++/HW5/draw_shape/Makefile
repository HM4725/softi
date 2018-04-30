draw_shape : draw_shape.o draw_shape_main.o
	g++ -o draw_shape draw_shape.o draw_shape_main.o

draw_shape.o : draw_shape.cc
	g++ -c -o draw_shape.o draw_shape.cc -Wall -g

draw_shape_main.o : draw_shape_main.cc
	g++ -c -o draw_shape_main.o draw_shape_main.cc -std=c++11 -Wall -g

clean :
	rm *.o draw_shape
