CC = g++

all: cw

cw: main.o functions.o check_functions.o secondary_functions.o inputFunctions.o
	$(CC) -o cw main.o functions.o secondary_functions.o check_functions.o inputFunctions.o

main.o: main.cpp BMP.hpp functions.hpp inputFunctions.hpp
	$(CC) -c main.cpp

functions.o: functions.cpp BMP.hpp
	$(CC) -c functions.cpp

check_functions.o: check_functions.cpp functions.hpp secondary_functions.hpp BMP.hpp
	$(CC) -c check_functions.cpp

secondary_functions.o: secondary_functions.cpp BMP.hpp
	$(CC) -c secondary_functions.cpp

inputFunctions.o: inputFunctions.cpp
	$(CC) -c inputFunctions.cpp

clean:
	rm -f *.o cw