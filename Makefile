#Makefile to compile the project which SImulates a Cache
CC= g++
CFLAGS=  -g -Wall
SOURCES=  Cache.cpp CacheSimulator.cpp Line.cpp Set.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=cacheSimulator

.SUFFIXES: .cpp .o

.cpp.o:
	$(CC) $(CFALGS) -c $< 


cacheSimulator: Cache.o CacheSimulation.o Line.o Set.o
	$(CC) $(CFLAGS) Cache.o CacheSimulation.o Line.o Set.o -o $(EXECUTABLE)

CacheSimulation.o: CacheSimulation.cpp CacheSimulation.h Cache.o Set.o Line.o
	$(CC) $(CFLAGS) -c CacheSimulation.cpp

Cache.o: Cache.cpp Cache.h Set.o Line.o
	$(CC) $(CFLAGS) -c Cache.cpp	

Set.o: Set.cpp Set.h Line.o
	$(CC) $(CFLAGS) -c Set.cpp

Line.o: Line.cpp Line.h
	$(CC) $(CFLAGS) -c Line.cpp

clean:
	rm -rf *o cacheSimulator

