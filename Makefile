CC=g++
SOURCES=huffman_table.cpp

.PHONY: all build test clean

all:
	@echo make - build, test, clean

build:
	$(CC) $(SOURCES) main.cpp -o huffman

test:
	$(CC) $(SOURCES) test.cpp -o test

clean:
	rm -f huffman
	rm -f test
