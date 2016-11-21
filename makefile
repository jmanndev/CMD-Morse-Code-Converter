all: prog

prog: main.o BinaryConverter.o binnode.o bintree.o const_iterator.o
	g++ main.o BinaryConverter.o binnode.o bintree.o const_iterator.o -o prog 

main.o: main.cpp
	g++ -c main.cpp

BinaryConverter.o: BinaryConverter.cpp
	g++ -c BinaryConverter.cpp

Utility.o: Utility.cpp
	g++ -c Utility.cpp
