CC=clang

all: msock msock_server msock_client

%: SRC/%.c
	$(CC) -c $^ -o $@.o
