COMPILER=gcc
INCLUDE_DIR=include
CFLAGS=-I$(INCLUDE_DIR) -w -c -std=gnu90 -pedantic -fPIC

all: bin/str.o bin/striterator.o bin/list.o bin/utils.o
	$(COMPILER) -shared -o bin/libc-candy.so bin/str.o bin/striterator.o bin/list.o bin/utils.o

bin/list.o: include/constants.h include/list.h src/list.c
	$(COMPILER) $(CFLAGS) src/list.c -o bin/list.o

bin/str.o: include/constants.h include/str.h src/str.c
	$(COMPILER) $(CFLAGS) src/str.c -o bin/str.o

bin/striterator.o: include/constants.h include/striterator.h src/striterator.c
	$(COMPILER) $(CFLAGS) src/striterator.c -o bin/striterator.o

bin/utils.o: include/constants.h include/utils.h src/utils.c
	$(COMPILER) $(CFLAGS) src/utils.c -o bin/utils.o

test_str: tests/test_str.c bin/str.o bin/striterator.o bin/list.o bin/utils.o
	$(COMPILER) $(CFLAGS) tests/test_str.c -o bin/test_str.o
	$(COMPILER) bin/str.o bin/striterator.o bin/utils.o bin/test_str.o -o bin/test_str.out

test_list: tests/test_str.c tests/test_list.c bin/str.o bin/striterator.o bin/list.o bin/utils.o
	$(COMPILER) $(CFLAGS) tests/test_list.c -o bin/test_list.o
	$(COMPILER) bin/str.o bin/striterator.o bin/list.o bin/utils.o bin/test_list.o -o bin/test_list.out

clean:
	rm -rf bin/*.o bin/*.so
