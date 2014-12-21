C = g++ -Wall
TAR = MyLinkedList.cpp MyLinkedList.h MyHashMap.cpp MyHashMap.h \
		HashMapBinaryOperations.cpp Makefile

HashMapBinaryOperations : MyLinkedList.o MyHashMap.o HashMapBinaryOperations.o
	$(C) MyLinkedList.o MyHashMap.o HashMapBinaryOperations.o -o HashMapBinaryOperations

HashMapBinaryOperations.o : HashMapBinaryOperations.cpp MyLinkedList.h MyHashMap.h
	$(C) HashMapBinaryOperations.cpp -c

TestBinaryOp: MyLinkedList.o MyHashMap.o TestHashMapBinFuncs.o
	$(C) MyLinkedList.o MyHashMap.o TestHashMapBinFuncs.o -o testBinaryOp
	
TestHashMapBinFuncs.o : TestHashMapBinFuncs.cpp MyLinkedList.h MyHashMap.h
	$(C) TestHashMapBinFuncs.cpp -c

MyLinkedList.o : MyLinkedList.cpp MyLinkedList.h
	$(C) MyLinkedList.cpp -c

MyHashMap.o : MyHashMap.cpp MyHashMap.h MyLinkedList.h
	$(C) MyHashMap.cpp -c		

TestSimpleHash: MyLinkedList.o MyHashMap.o HashSimpleCheck.o
	$(C) MyLinkedList.o MyHashMap.o HashSimpleCheck.o -o TestSimpleHash

HashSimpleCheck.o: HashSimpleCheck.cpp MyHashMap.h
	$(C) HashSimpleCheck.cpp -c

TestLinkedList: MyLinkedList.o ListExample.o
	$(C) MyLinkedList.o ListExample.o -o TestLinkedList

ListExample.o: ListExample.cpp MyLinkedList.h
	$(C) ListExample.cpp -c

test: TestLinkedList TestSimpleHash TestBinaryOp
	TestLinkedList
	TestSimpleHash
	TestBinaryOp

tar: $(TAR)
	tar cvf ex1.tar $(TAR)
	
clean: 
	rm -f *.o TestLinkedList TestSimpleHash TestBinaryOp
.PHONY: clean all test TestLinkedList TestSimpleHash testBinaryOp

  