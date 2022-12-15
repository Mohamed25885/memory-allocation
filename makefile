CC = gcc
CFLAGS = -Wall
LDFLAGS = 
OBJ = memory-management.o  allocator.o
EXEC = memory-management

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) $(LDFLAGS)


clean:
	rm *.o

open: 
	./$(EXEC)

cleanTxt:
	del *.txt