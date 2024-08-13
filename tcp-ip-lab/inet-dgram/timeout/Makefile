# FILE: Makefile for programs to demonstrate timeouts in UDP sockets

PROGS=select

TOP_LEVEL_OBJS=udp_timeout.o
MIDDLE_LEVEL_OBJS=via_select.o
BOTTOM_LEVEL_OBJS=common.o socket_address.o
OBJS=$(BOTTOM_LEVEL_OBJS) $(MIDDLE_LEVEL_OBJS) $(TOP_LEVEL_OBJS)

all: $(PROGS)

select: $(BOTTOM_LEVEL_OBJS)  via_select.o $(TOP_LEVEL_OBJS)
	$(CC) -o select $(BOTTOM_LEVEL_OBJS)  via_select.o $(TOP_LEVEL_OBJS)

clean:
	rm -f $(OBJS) *~ $(PROGS) #*
