all: unique unittests

unique: unique.o tree.o
	clang unique.o tree.o -o unique

unittests: unittests.o tree.o
	clang unittests.o tree.o -o unittests

unique.o: unique.c tree.h
	clang -Wall -Wextra -Wpedantic -gdwarf-4 -c unique.c -o unique.o

unittests.o: unittests.c tree.h
	clang -Wall -Wextra -Wpedantic -gdwarf-4 -c unittests.c -o unittests.o

tree.o: tree.c tree.h
	clang -Wall -Wextra -Wpedantic -gdwarf-4 -c tree.c -o tree.o

clean:
	rm -f unique unittests *.o
