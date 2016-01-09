
all: vigenere


vigenere: cipherTools vigenere.o main.cpp
	g++ -Wall -I../Common/ ../Common/cipherTools.o vigenere.o main.cpp -o vigenere

vigenere.o: vigenere.cpp
	g++ -Wall -I../Common/ -c vigenere.cpp

cipherTools:
	$(MAKE) -C ../Common/


clean:
	rm *o vigenere

