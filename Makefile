# CSF Fall 2020
# Cache simulator
# Assignment 3
# 1. Steven (Bumjin) Kim
# 2. Rebecca Shao

CXX = g++
CXXFLAGS = -Wall -Wextra --pedantic

%.o : %.c
	$(CXX) -c $(CXXFLAGS) -o $*.o $<

csim : cache.o cacheblock.o cacheconfig.o cachesimulator.o memory.o counter.o main.o utils.o
	$(CXX) -o $@ cache.o cacheblock.o cacheconfig.o cachesimulator.o memory.o counter.o main.o utils.o

counter.o: counter.h
memory.o: memory.h counter.h
cache.o: cache.h cacheblock.h cacheconfig.h cache.cpp
cacheblock.o: cache.h cacheblock.h counter.h memory.h cacheblock.cpp
cacheconfig.o: cacheconfig.h utils.h cacheconfig.cpp
csim.o.o: cache.h cacheblock.h cacheconfig.h \
                  cachesimulator.h counter.h memory.h utils.h cachesimulator.cpp
main.o: cache.h cacheconfig.h cachesimulator.h counter.h utils.h \
        memory.h main.cpp
utils.o: cacheconfig.h utils.h

solution.zip :
	rm -f solution.zip
	zip -9r $@ Makefile Makefile cache.cpp cache.h cacheblock.cpp cacheblock.h cacheconfig.cpp cacheconfig.h cachesimulator.cpp cachesimulator.h counter.h counter.cpp main.cpp memory.cpp memory.h utils.cpp utils.h README

clean :
	rm -f *.o csim solution.zip
