CC=gcc
OBJS_C=client.o
OBJS_S=server.o
all: client server

client:$(OBJS_C)
	gcc -o client $(OBJS_C)

server:$(OBJS_S)
	gcc -o server $(OBJS_S)

.PHONY: clean
clean:
	rm -f client server $(OBJS_C) $(OBJS_S)

