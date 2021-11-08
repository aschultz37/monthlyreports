CC = g++
CFLAGS = -std=c++2a

reportgenerator: main.o reportgenerator.o
	$(CC) $(CFLAGS) -o reportgenerator main.o reportgenerator.o

main.o: main.cpp reportgenerator.cpp reportgenerator.hpp

reportgenerator.o: reportgenerator.cpp reportgenerator.hpp