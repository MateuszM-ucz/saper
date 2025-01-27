CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: gra

gra: main.o plansza.o wynik.o gra.o
	$(CC) $(CFLAGS) -o gra main.o plansza.o wynik.o gra.o

main.o: main.c plansza.h wynik.h gra.h
	$(CC) $(CFLAGS) -c main.c

plansza.o: plansza.c plansza.h
	$(CC) $(CFLAGS) -c plansza.c

wynik.o: wynik.c wynik.h
	$(CC) $(CFLAGS) -c wynik.c

gra.o: gra.c gra.h plansza.h
	$(CC) $(CFLAGS) -c gra.c

clean:
	rm -f *.o gra
