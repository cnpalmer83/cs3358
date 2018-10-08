bag: Bag.o main.o
	g++ Bag.o main.o -o bag
Bag.o: bag.cpp bag1.h
	g++ -Wall -ansi -pedantic -std=c++11 -c bag.cpp
main.o: main.cpp bag.cpp bag1.h
	g++ -Wall -ansi -pedantic -std=c++11 -c main.cpp

clean:
	@rm -rf Bag.o main.o
cleanall:
	@rm -rf Bag.o main.o bag
