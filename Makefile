all: main

main: geometry.o 
	g++ -o main geometry.o -std=c++17

geometry.o: geometry.cpp
	g++ -o geometry.o -c geometry.cpp -std=c++17

.PHONY: clean

clean:
	rm -rf *.o main
