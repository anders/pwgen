CC?=clang
CFLAGS?=-Wall -Wextra -Os -fobjc-arc
TARGET=sf-pwgen
SRC=sf-pwgen.m
LIBS=-framework Foundation -framework CoreFoundation -framework SecurityFoundation

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

format:
	clang-format -i -style=Mozilla $(SRC) $(wildcard SecurityFoundation/*.h)

clean:
	rm -f $(TARGET)

.PHONY: clean
