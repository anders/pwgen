CFLAGS=-Wall -Wextra -Os
TARGET=pwgen
SRC=pwgen.m
OBJ=$(SRC:.m=.o)
LIBS=-framework Foundation -framework CoreFoundation -framework SecurityFoundation

.m.o:
	$(CC) $(CFLAGS) -c $*.m -o $*.o

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

format:
	clang-format -i -style=Mozilla $(SRC) $(wildcard SecurityFoundation/*.h)

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: clean
