CC = gcc
CFLAGS = -g -w -O3

all: libpngparser tests

clean:
	rm -f libpngparser.a tests *.o

.PHONY: all clean fix_all_bugs tests

libpngparser: pngparser.h pngparser.c crc.c crc.h
	$(CC) $(CFLAGS) -c pngparser.c crc.c
	ar rcs libpngparser.a pngparser.o crc.o

filter: libpngparser filter.c
	$(CC) $(CFLAGS) -o filter filter.c libpngparser.a -lz -lm

tests: tests.o filter.o
	$(CC) $(CFLAGS) -Werror -Wall tests.o filter.o libpngparser.a -lcheck -lm -lz -lrt -lpthread -lsubunit -o tests

tests.o: tests.c filter.h 
