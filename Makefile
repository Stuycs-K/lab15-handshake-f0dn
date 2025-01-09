# Running files
client: compile-client
	@./client.out

basic: compile-basic
	@./basic.out

persistent: compile-persistent
	@./persistent.out

server: compile-server
	@./server.out

# Compiling files
compile: compile-client compile-basic compile-persistent compile-server

compile-client: basic_client.o pipe_networking.o
	@gcc -o client.out basic_client.o pipe_networking.o

compile-basic: basic_server.o pipe_networking.o
	@gcc -o basic.out basic_server.o pipe_networking.o

compile-persistent: persistent_server.o pipe_networking.o
	@gcc -o persistent.out persistent_server.o pipe_networking.o

compile-server: forking_server.o pipe_networking.o
	@gcc -o server.out forking_server.o pipe_networking.o

# Compiling object files
basic_client.o: basic_client.c pipe_networking.h
	@gcc -c basic_client.c -Wall

basic_server.o: basic_server.c pipe_networking.h
	@gcc -c basic_server.c -Wall

persistent_server.o: persistent_server.c pipe_networking.h
	@gcc -c persistent_server.c -Wall

forking_server.o: forking_server.c pipe_networking.h
	@gcc -c forking_server.c -Wall

pipe_networking.o: pipe_networking.c pipe_networking.h
	@gcc -c pipe_networking.c

# Cleaning directory
clean:
	@rm -f *.o *.out
