
.PHONY: clean

all: affine


affine: cipherTools affine.o main.cpp
	g++ -Wall -I../Common/ ../Common/cipherTools.o affine.o main.cpp -o affine

affine.o: affine.cpp
	g++ -Wall -I../Common/ -c affine.cpp

cipherTools:
	$(MAKE) -C ../Common/


clean:
	rm *o affine

