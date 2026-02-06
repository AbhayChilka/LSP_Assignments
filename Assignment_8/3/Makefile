CC = gcc
CFLAGS = -Wall -Wextra -O2
SRC = Demo.c
TARGET = app

$(TARGET): 
		$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

run :
	./$(TARGET)

clean:
	rm -f $(TARGET)

help :
	@echo To compile the program run make command  = "make"
	@echo To execute the program run make run command = "make run"
	@echo to delete the executable i.e binary file run make clean = "make clean"

