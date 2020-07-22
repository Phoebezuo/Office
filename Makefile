CC=clang
CFLAGS=-Werror=vla -Wextra -Wall -Wshadow -Wswitch-default -std=c11 -g
# CFLAGS=-std=c11 -g
CFLAG_SAN=$(CFLAGS) -fsanitize=address

.PHONY: clean

clean:
	rm -f *.o
	rm -f all

office.o: office.c
	$(CC) -c $(CFLAGS) $^ -o $@

main.o: main.c
	$(CC) -c $(CFLAGS) $^ -o $@

all: main.o office.o
	$(CC) $(CFLAG_SAN) $^ -o $@
	./all
