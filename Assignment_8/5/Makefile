CC = gcc

app: client.c server.a
	$(CC) client.c -o app -L. -lserver -I.

server.a : server.o
	ar rcs libserver.a server.o

server.o: server.c 
	$(CC) -c server.c -o server.o

clean:
	rm -f app server.o libserver.a

run:
	./app



