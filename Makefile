all:
	clang -arch i386 -arch x86_64 -Wall -Wextra -O2 -framework CoreFoundation -framework SecurityFoundation pwgen.c -o pwgen

clean:
	rm -f pwgen
