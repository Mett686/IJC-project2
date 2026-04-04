export LC_ALL = cs_CZ.utf8
CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -MMD -MP
LDLIBS =
xlogin = xknotem00

TARGETS = primes primes-i no-comment

all: $(TARGETS)

-include *.d

primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

primes-i: primes-i.o eratosthenes-i.o bitarray-i.o error.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

tac: tac.o
	$(CC) $(CFLAGS) -o $@ $^


no-comment.o: CFLAGS += -D_POSIX_C_SOURCE 

%-i.o: %.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


run: primes primes-i
	ulimit -s unlimited && ./primes
	ulimit -s unlimited && ./primes-i

clean:
	rm -f *.o *.d $(xlogin).zip

zip:
	zip $(xlogin).zip *.c *.h Makefile

.PHONY: all run clean zip
