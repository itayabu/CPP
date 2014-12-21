C= g++ -Wall
TAR= MatrixInterface.h SparseMatrix.h SparseMatrix.cpp RegMatrix.h RegMatrix.cpp MyMatrix.h \
	MyMatrix.cpp Makefile 
demo : DemoMyMatrix.o MyMatrix.o RegMatrix.o SparseMatrix.o
	$(C) DemoMyMatrix.o MyMatrix.o RegMatrix.o SparseMatrix.o -o DemoMyMatrix

RegMatrix.o: RegMatrix.cpp RegMatrix.h Vector.h MatrixInterface.h
	$(C) RegMatrix.cpp -c
	
SparseMatrix.o: SparseMatrix.cpp SparseMatrix.h Map.h MatrixInterface.h
	$(C) SparseMatrix.cpp -c

MyMatrix.o: MyMatrix.cpp MyMatrix.h SparseMatrix.h Map.h
	$(C) MyMatrix.cpp -c

DemoMyMatrix.o: MyMatrix.h DemoMyMatrix.cpp
	$(C) DemoMyMatrix.cpp -c
tar: $(TAR)
	tar cvf ex2.tar $(TAR)
	
all: RegMatrix.cpp RegMatrix.h Vector.h MatrixInterface.h SparseMatrix.cpp SparseMatrix.h Map.h MyMatrix.cpp MyMatrix.h DemoMyMatrix.cpp
	$(C) RegMatrix.cpp -c
	$(C) SparseMatrix.cpp -c
	$(C) MyMatrix.cpp -c
	$(C) DemoMyMatrix.cpp -c

clean:
	rm -f *.o test
.PHONY: clean all tar

