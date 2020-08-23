CC = gcc -Wall
OBJECTS = client.o  server.o pipe_test.o

.PHONY:all 
all: client server pipe_test

client: client.o
	$(CC) client.o -o client

server: server.o
	$(CC) server.o -o server

pipe_test: pipe_test.o
	$(CC) pipe_test.o -o pipe_test

.PHONY:clean
clean:  
	rm $(OBJECTS) client server pipe_test
