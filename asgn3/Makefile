lcr: lcr.o game.o randi.o
	clang lcr.o game.o randi.o -o lcr

lcr.o: lcr.c
	clang -c lcr.c

game.o: game.c
	clang -c game.c

randi.o: randi.c
	clang -c randi.c

clean:
	rm -f lcr *.o
