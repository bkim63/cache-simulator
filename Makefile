CC=g++
CFLAGS=-std=c++11 -Wall -Wextra -pedantic -g

csim: main.o utils.o cache.o cacheblock.o cacheset.o
	$(CC) -o csim main.o utils.o cache.o cacheblock.o cacheset.o

main.o: main.cpp utils.h cacheblock.h cacheset.h cache.h
	$(CC) $(CFLAGS) -c main.cpp

utils.o: utils.cpp utils.h
	$(CC) $(CFLAGS) -c utils.cpp

cache.o: cache.cpp cache.h cacheset.h
	$(CC) $(CFLAGS) -c cache.cpp

cacheblock.o: cacheblock.cpp cacheblock.h
	$(CC) $(CFLAGS) -c cacheblock.cpp

cacheset.o: cacheset.cpp cacheset.h cacheblock.h
	$(CC) $(CFLAGS) -c cacheset.cpp

clean:
	rm -rf *.o csim

.PHONY: solution.zip
solution.zip :
	rm -f solution.zip
	zip -9r $@ Makefile *.h *.cpp README
