.PHONY: all clean

all: xd bad_xd

xd: xd.o
	clang xd.o -o xd

bad_xd: bad_xd.o
	clang bad_xd.o -o bad_xd

xd.o: xd.c
	clang -Wall -Wextra -Werror -c xd.c -o xd.o

bad_xd.o: bad_xd.c
	clang -Wall -Wextra -Werror -c bad_xd.c -o bad_xd.o

clean:
	rm -f xd bad_xd *.o
