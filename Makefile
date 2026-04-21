CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -g -MMD -MP -DMY_HASH_FUNCTION
LDLIBS =
xlogin = xknotem00

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
check: tac maxwordcount maxwordcount-dynamic
	./tac <htab.h
	@echo "################################################################"
	./maxwordcount <htab.h
	@echo
	LD_LIBRARY_PATH=. ./maxwordcount-dynamic <htab.h

run: maxwordcount maxwordcount-dynamic maxwordcount-cpp
	(cat tests/longword.txt) | ./maxwordcount
	(cat tests/longword.txt) | LD_LIBRARY_PATH=. ./maxwordcount-dynamic
	(cat tests/longword.txt) | ./maxwordcount-cpp

	(cat tests/romeo_julie.txt) | ./maxwordcount
	(cat tests/romeo_julie.txt) | LD_LIBRARY_PATH=. ./maxwordcount-dynamic
	(cat tests/romeo_julie.txt) | ./maxwordcount-cpp

	(cat maxwordcount.c) | ./maxwordcount
	(cat maxwordcount.c) | LD_LIBRARY_PATH=. ./maxwordcount-dynamic
	(cat maxwordcount.c) | ./maxwordcount-cpp
	
	(cat .zadani.txt) | ./maxwordcount
	(cat .zadani.txt) | LD_LIBRARY_PATH=. ./maxwordcount-dynamic
	(cat .zadani.txt) | ./maxwordcount-cpp

run_valgrind:
	valgrind ./maxwordcount <tests/longword.txt
	LD_LIBRARY_PATH=. valgrind ./maxwordcount-dynamic <tests/longword.txt

	valgrind ./maxwordcount <tests/romeo_julie.txt
	LD_LIBRARY_PATH=. valgrind ./maxwordcount-dynamic <tests/romeo_julie.txt

################################################################
clean:
	rm -f *.o *.d $(xlogin).zip

zip:
	zip $(xlogin).zip *.c *.h Makefile

-include *.d

.PHONY: run clean zip
