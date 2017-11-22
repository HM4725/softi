test : omok.o omok_main.o
	g++ -o test omok.o omok_main.o

omok.o : omok.cc
	g++ -c -o omok.o omok.cc -Wall -g

omok_main.o : omok_main.cc
	g++ -c -o omok_main.o omok_main.cc -Wall -g

clean :
	rm *.o test
