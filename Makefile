CC=clang
CFLAGS=-arch x86_64 -arch i386 -Wall -Wextra -O2 -g
TARGET=pwgen
SRC=pwgen.c
OBJ=$(SRC:.c=.o)
LIBS=-framework CoreFoundation -framework SecurityFoundation

.c.o:
	$(CC) $(CFLAGS) -c $*.c -o $*.o

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: clean
