CFLAGS=-Wall -Wextra -Os
TARGET=pwgen
SRC=pwgen.c
OBJ=$(SRC:.c=.o)
LIBS=-framework Foundation -framework CoreFoundation -framework SecurityFoundation

.c.o:
	$(CC) $(CFLAGS) -c $*.c -o $*.o

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: clean
