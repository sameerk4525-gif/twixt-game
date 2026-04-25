CC = gcc
CFLAGS = -Wall

all: twixt

twixt: main.o logic.o board.o
	$(CC) $(CFLAGS) main.o logic.o board.o -o twixt

main.o: main.c game.h
	$(CC) $(CFLAGS) -c main.c

logic.o: logic.c game.h
	$(CC) $(CFLAGS) -c logic.c

board.o: board.c game.h
	$(CC) $(CFLAGS) -c board.c

run: twixt
	./twixt

clean:
	rm -f *.o twixt
