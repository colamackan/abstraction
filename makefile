CC = gcc

FLAGS = -Wall -ggdb -g -std=c99

all: db

db: db.o treedb.o logo.o
	$(CC) $(FLAGS) -o db db.o treedb.o logo.o

db.o: db.c treedb.h logo.h
	$(CC) $(FLAGS) -c db.c

treedb.o: treedb.c treedb.h
	$(CC) $(FLAGS) -c treedb.c

logo.o: logo.c logo.h treedb.h
	$(CC) $(FLAGS) -c logo.c

main: db.c
	$(CC) $(FLAGS) -o main db.c

test: db_test.c treedb.c treedb.h
	$(CC) $(FLAGS) db_test.c treedb.c -o t -lcunit
	./t

run: all

.PHONY: clean

clean:
	rm -rf *.o
	rm -rf t
	rm -rf db
