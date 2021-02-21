CC= g++
CFLAGS= -Wextra -Wvla -Wall -std=c++14 -g
CODEFILES=  ex3.tar my_set.hpp my_set.h Makefile

# make all
all: testset

# make testset
testset: my_set_tester.o
	$(CC)   my_set_tester.o  -o  testset


# make testset object file
my_set_tester.o: my_set_tester1.cpp  my_set.h  my_set.hpp
	$(CC)  $(CFLAGS)  my_set_tester1.cpp

# generating tar file
tar:
	tar -cvf $(CODEFILES)

# make clean
clean:
	-rm -f *.o testset ex3 my_set.o

.PHONY: clean