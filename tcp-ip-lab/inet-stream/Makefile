# Makefile for TCP applications

PROGS=large-stream-cli large-stream-serv 

COMMON_OBJS=../common-code/null_str.o ../common-code/socket_address.o 

MY_OBJS=large-stream-cli.o large-stream-serv.o

all: $(PROGS)

large-stream-cli: large-stream-cli.o  $(COMMON_OBJS)
	$(CC) -c large-stream-cli.c
	$(CC) -o large-stream-cli $(COMMON_OBJS) large-stream-cli.o

large-stream-serv: large-stream-serv.o  $(COMMON_OBJS)
	$(CC) -c large-stream-serv.c
	$(CC) -o large-stream-serv $(COMMON_OBJS) large-stream-serv.o

clean:
	rm -f $(MY_OBJS) *~ #*
