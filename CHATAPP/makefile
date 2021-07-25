CC=clang
BINPATH=../BIN

all: server client

server: server.o
	$(CC) $^ ../MSOCK/msock.o -o $(BINPATH)/$@

client: client.o
	$(CC) $^ ../MSOCK/msock.o -o $(BINPATH)/$@

%.o: SRC/%.c
	$(CC) -I ../MSOCK/SRC -c $^ -o $@


