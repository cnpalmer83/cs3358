a4s2: sequenceTest.o
	g++ sequenceTest.o -o a4s2
sequenceTest.o: sequenceTest.cpp
	g++ -Wall -ansi -pedantic -std=c++11 -c sequenceTest.cpp

test:
	./a4s2 auto < a4test.in > a4test.out
clean:
	@rm -rf sequenceTest.o
cleanall:
	@rm -rf sequenceTest.o a4s2
