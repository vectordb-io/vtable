CC:=g++
CFLAGS+=-c -Wall -g -std=c++17
INCLUDES=-I./ -I./third_party/leveldb.1.22/leveldb/include

OBJS=main.o util.o vtable.o
LIBS=-lpthread -lleveldb
LFLAGS=-L/usr/local/lib -L./third_party/leveldb.1.22/leveldb/b

main: $(OBJS)
	$(CC) $^ -o $@ $(LIBS) $(LFLAGS)

%.o: %.cc %.h
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $<

clean:
	rm -rf *.o
	rm -rf main

