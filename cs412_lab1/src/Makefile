CC = gcc
CFLAGS = -g -w

all: libpngparser solid checkerboard filter circle rect resize_image

clean:
	rm -f libpngparser.a solid checkerboard filter circle rect resize_image

.PHONY: all clean fix_all_bugs

libpngparser: pngparser.h pngparser.c crc.c crc.h
	$(CC) $(CFLAGS) -c pngparser.c crc.c
	ar rcs libpngparser.a pngparser.o crc.o
	rm pngparser.o crc.o

solid: libpngparser solid.c
	$(CC) $(CFLAGS) -o solid solid.c libpngparser.a -lz

checkerboard: libpngparser checkerboard.c
	$(CC) $(CFLAGS) -o checkerboard checkerboard.c libpngparser.a -lz

filter: libpngparser filter.c
	$(CC) $(CFLAGS) -o filter filter.c libpngparser.a -lz

circle: libpngparser circle.c
	$(CC) $(CFLAGS) -o circle circle.c libpngparser.a -lz -lm

rect: libpngparser rect.c
	$(CC) $(CFLAGS) -o rect rect.c libpngparser.a -lz

resize_image: libpngparser resize.c
	$(CC) $(CFLAGS) -o resize_image resize.c libpngparser.a -lm -lz

fix_all_bugs:
	firefox https://www.youtube.com/watch?v=dQw4w9WgXcQ