CXX = clang++

CXXFLAGS = -std=c++11 -Wall -Wextra

BINARIES = main

all: ${BINARIES}

main: testMain.o HoffmanEncoding.o TrieNode.o MinHeap.o
	${CXX} $^ -o $@

prog2: ${BINARIES}
	./main

clean:
	/bin/rm -f ${BINARIES} *.o