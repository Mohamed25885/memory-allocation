CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm -ljson-c
OBJ = memory_management.o  allocator.o linked_list.o json_handler.o
EXEC = memory_management

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) $(LDFLAGS)


clean:
	rm *.o

open: 
	./$(EXEC)

cleanTxt:
	del *.txt