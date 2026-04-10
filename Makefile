CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -MMD -MP -DMY_HASH_FUNCTION
LDLIBS =
xlogin = xknotem00

LD_LIBRARY_PATH = .
LIB_HTAB = $(wildcard htab_*.c)

all: tac maxwordcount maxwordcount-dynamic libhtab.a libhtab.so

################################################################
tac: tac.o
	$(CC) $(CFLAGS) -o $@ $^

maxwordcount: maxwordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -o $@ $^

maxwordcount-dynamic: maxwordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) -o $@ maxwordcount.o io.o -L. -lhtab

################################################################
libhtab.a: $(LIB_HTAB:.c=.o)
	ar rcs $@ $^

libhtab.so: $(LIB_HTAB:.c=.pic.o)
	$(CC) $(CFLAGS) -shared -o $@ $^

################################################################
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.pic.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

################################################################
run: maxwordcount maxwordcount-dynamic tac
	(cat maxwordcount.c) | ./maxwordcount
	(cat maxwordcount.c) | LD_LIBRARY_PATH=. ./maxwordcount-dynamic
	(cat maxwordcount.c) | ./a.out
	

clean:
	rm -f *.o *.d $(xlogin).zip

zip:
	zip $(xlogin).zip *.c *.h Makefile

-include *.d

.PHONY: run clean zip
