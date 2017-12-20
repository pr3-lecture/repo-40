.PHONY: all clean
all: crypter
clean:
	rm -f main.o crypter
main.o: main.c
	cc -Wall -c main.c
crypter: main.o
	cc -o crypter main.o
