.PHONY: all clean
all: decrypt encrypt
clean:
	rm -f main.o decrypt
	rm -f main.o encrypt
main.o: main.c
	cc -Wall -c main.c crypto.c
decrypt: main.o
	cc -o decrypt main.o
encrypt: main.o
	cc -o encrypt main.o
