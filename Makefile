all:
	clang -Wall -Wextra -O2 -framework CoreFoundation -framework SecurityFoundation pwgen.c -o pwgen

clean:
	rm -f pwgen