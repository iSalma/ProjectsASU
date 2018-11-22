all : matrix CMatrix.h
	./matrix

matrix: matrix.o cmatrix.o
	g++ main.o CMatrix.o -o matrix
	

matrix.o : main.cpp
	g++ -std=c++0x -c main.cpp
cmatrix.o : CMatrix.cpp
	g++ -std=c++0x -c CMatrix.cpp
clean :
	rm matrix CMatrix.o main.o

	
