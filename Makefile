CC = g++
CFLAGS = -std=c++11 -g -Wall
OBJECTS = main.o PeacockHash.o BOBHash.o hash_function.o md5.o key-value.o sha1.o
all : peacock

peacock : $(OBJECTS)
	$(CC) $(CFLAGS) -o peacock $(OBJECTS)

main.o : main.cpp PeacockHash.h
	$(CC) $(CFLAGS) -c main.cpp

PeacockHash.o : PeacockHash.cpp PeacockHash.h
	$(CC) $(CFLAGS) -c PeacockHash.cpp

BOBHash.o :BOBHash.cpp BOBHash.h
	$(CC) $(CFLAGS) -c BOBHash.cpp

hash_function.o : hash_function.cpp sha1.h md5.h
	$(CC) $(CFLAGS) -c hash_function.cpp

md5.o : md5.cpp md5.h
	$(CC) $(CFLAGS) -c md5.cpp

key-value.o : key-value.cpp key-value.h
	$(CC) $(CFLAGS) -c key-value.cpp

sha1.o : sha1.cpp sha1.h
	$(CC) $(CFLAGS) -c sha1.cpp

clean:
	rm *.o 