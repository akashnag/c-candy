COMPILER=gcc
INCLUDE_DIR=include
CFLAGS=-I$(INCLUDE_DIR) -w -c -std=gnu90 -pedantic -fPIC

all: bin/str.o
	$(COMPILER) -shared -o libccandy.so bin/str.o

bin/str.o: include/constants.h include/str.h src/str.c
	$(COMPILER) $(CFLAGS) src/str.c -o bin/str.o

clean:
	rm -rf bin/*.o bin/*.so
