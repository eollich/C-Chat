CC=clang
BINPATH=../BIN

all: server client

server: server.o
	$(CC) $^ ../MSOCK/msock.o ../MSOCK/msock_server.o -o $(BINPATH)/$@

client: client.o
	$(CC) $^ ../MSOCK/msock.o ../MSOCK/msock_client.o -o $(BINPATH)/$@

%.o: SRC/%.c
	$(CC) -I ../MSOCK/SRC -c $^ -o $@


