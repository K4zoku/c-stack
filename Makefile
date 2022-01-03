CC=cc
CFLAGS=-g -fPIC -O2 -Wall -Wextra -std=c89

default: clean test

clean:
	rm -f cstack-test

test: cstack-test
	./cstack-test

memcheck: cstack-test
	valgrind ./cstack-test

cstack-test:
	$(CC) $(CFLAGS) test.c -o cstack-test
