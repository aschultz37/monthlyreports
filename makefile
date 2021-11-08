CC = g++
CFLAGS = -std=c++2a

reportgenerator: main.o reportgenerator.o bloodreport.o
	$(CC) $(CFLAGS) -o reportgenerator main.o reportgenerator.o bloodreport.o

main.o: main.cpp reportgenerator.o

reportgenerator.o: reportgenerator.cpp reportgenerator.hpp bloodreport.o

bloodreport.o: bloodreport.cpp bloodreport.hpp