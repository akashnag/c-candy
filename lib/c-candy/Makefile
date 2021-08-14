COMPILER=gcc
INCLUDE_DIR=include
CFLAGS=-I$(INCLUDE_DIR) -w -c -std=gnu90 -pedantic -fPIC

all: bin/str.o bin/striterator.o bin/list.o
	$(COMPILER) -shared -o bin/libc-candy.so bin/str.o bin/striterator.o bin/list.o

bin/list.o: include/constants.h include/list.h src/list.c
	$(COMPILER) $(CFLAGS) src/list.c -o bin/list.o

bin/str.o: include/constants.h include/str.h src/str.c
	$(COMPILER) $(CFLAGS) src/str.c -o bin/str.o

bin/striterator.o: include/constants.h include/striterator.h src/striterator.c
	$(COMPILER) $(CFLAGS) src/striterator.c -o bin/striterator.o

clean:
	rm -rf bin/*.o bin/*.so
