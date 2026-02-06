CC = gcc

app: Main.o Helper.o 
	$(CC) Main.o Helper.o -o app

Main.o:
	$(CC) -c Main.c

Helper.o:
	$(CC) -c Helper.c 

clean:
	rm -f app

run:
	./app

