CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -MMD -MP
LDLIBS =
xlogin = xknotem00

LIB_HTAB = $(wildcard htab_*.c)

all: tac maxwordcount clean #maxwordcount-dynamic libhtab.a libhtab.so

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

libhtab.so: $(LIB_HTAB:.c=pic.o)
	$(CC) $(CFLAGS) -shared -o $@ $^

################################################################
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.pic.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

################################################################
run: maxwordcount
	./maxwordcount

clean:
	rm -f *.o *.d $(xlogin).zip

zip:
	zip $(xlogin).zip *.c *.h Makefile

-include *.d

.PHONY: run clean zip
