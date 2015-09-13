CC=gcc
CFLAGS=-I . -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast -std=c99 -D_GNU_SOURCE=1 -Wall -g -Wno-unused-parameter

test: cmockery.c hmap_test.c hmap.c
	$(CC) $(CFLAGS) -o $@ $^

tests: test
	./test

clean:
	rm -f test
