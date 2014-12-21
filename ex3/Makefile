C = g++ -std=c++11 -Wall
TAR= Makefile Rational.cpp Matrix.hpp

GenericMatrixDriver: GenericMatrixDriver.o Rational.o
	$(C) GenericMatrixDriver.o Rational.o -o GenericMatrixDriver

Rational.o: Rational.cpp Rational.h 
	$(C) Rational.cpp -c

GenericMatrixDriver.o: GenericMatrixDriver.cpp Matrix.hpp
	$(C) GenericMatrixDriver.cpp -c
clean:
	rm -f *.o GenericMatrixDriver

tar:$(TAR)
	tar cvf ex3.tar Makefile Rational.cpp Matrix.hpp

	