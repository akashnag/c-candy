COMPILER=gcc
INCLUDE_DIR=include
CFLAGS=-I$(INCLUDE_DIR) -w -c -std=gnu90 -pedantic -fPIC

all: bin/str.o bin/striterator.o bin/list.o bin/stack.o bin/tuple.o bin/utils.o
	$(COMPILER) -shared -o bin/libc-candy.so bin/str.o bin/striterator.o bin/list.o bin/stack.o bin/tuple.o bin/utils.o

bin/tuple.o: include/constants.h include/utils.h include/tuple.h src/tuple.c
	$(COMPILER) $(CFLAGS) src/tuple.c -o bin/tuple.o

bin/stack.o: include/constants.h include/utils.h include/stack.h src/stack.c
	$(COMPILER) $(CFLAGS) src/stack.c -o bin/stack.o

bin/list.o: include/constants.h include/utils.h include/list.h src/list.c
	$(COMPILER) $(CFLAGS) src/list.c -o bin/list.o

bin/str.o: include/constants.h include/utils.h include/str.h src/str.c
	$(COMPILER) $(CFLAGS) src/str.c -o bin/str.o

bin/striterator.o: include/constants.h include/utils.h include/striterator.h src/striterator.c
	$(COMPILER) $(CFLAGS) src/striterator.c -o bin/striterator.o

bin/utils.o: include/constants.h include/utils.h src/utils.c
	$(COMPILER) $(CFLAGS) src/utils.c -o bin/utils.o

clean:
	rm -rf bin/*.o bin/*.so
