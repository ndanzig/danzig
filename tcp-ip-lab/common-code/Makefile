# FILE: tcp-ip-lab/private/code/Makefile

CC = gcc
TEST_EXE = test_socket test_socket_address
DEMO_EXE = udp_daytime_client
EXE = $(TEST_EXE) $(DEMO_EXE)

all: $(EXE)

test_socket: create_socket.o  test_socket.o
	gcc -o test_socket create_socket.o  test_socket.o

test_socket_address: socket_address.o  test_socket_address.o
	gcc -o test_socket_address \
		null_str.o  socket_address.o  test_socket_address.o

socket_address.o: null_str.o  

#-----------------------------------------------------------
clean: clean_demo clean_test clean_obj
	rm -f *~

clean_obj:
	rm -f *.o

clean_test: clean_obj
	rm -f $(TEST_EXE)

clean_demo: clean_obj
	rm -f $(DEMO_EXE)

