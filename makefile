CC = g++
CFLAGS = -std=c++2a -Ox

reportgenerator: main.o reportgenerator.o bloodreport.o tissuereport.o stoolreport.o
	$(CC) $(CFLAGS) -o reportgenerator main.o reportgenerator.o bloodreport.o tissuereport.o stoolreport.o

main.o: main.cpp reportgenerator.o

reportgenerator.o: reportgenerator.cpp reportgenerator.hpp bloodreport.o tissuereport.o stoolreport.o

bloodreport.o: bloodreport.cpp bloodreport.hpp

tissuereport.o: tissuereport.cpp tissuereport.hpp

stoolreport.o: stoolreport.cpp stoolreport.hpp