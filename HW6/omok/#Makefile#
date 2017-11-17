test : omok.o omok_main.o
	g++ -o test omok.o omok_main.o -Wall -g

omok.o : omok.cc
	g++ -c -o omok.o omok.cc

omok_main.o : omok_main.cc
	g++ -c -o omok_main.o omok_main.cc

clean :
	rm *.o test
