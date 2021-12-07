amrikac: main.o lex.o emit.o parse.o
	g++ main.o lex.o emit.o parse.o -o amrikac

main.o: bin/main.cpp
	g++ bin/main.cpp -c

lex.o: bin/lex.cpp
	g++ bin/lex.cpp -c

emit.o: bin/emit.cpp
	g++ bin/emit.cpp -c

parse.o: bin/parse.cpp
	g++ bin/parse.cpp -c
clean:
	rm -f *.o *.c *.out bin/*.gch amrikac
