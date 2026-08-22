CC = gcc
CFLAGS = -Wall -Wextra

allocator: main.o allocator.o test_allocator.o
	gcc main.o allocator.o test_allocator.o -o allocator

main.o: main.c allocator.h
	$(CC) $(CFLAGS) -c main.c

allocator.o: allocator.c allocator.h
	$(CC) $(CFLAGS) -c allocator.c

test_allocator.o: test_allocator.c allocator.h
	$(CC) $(CFLAGS) -c test_allocator.c

clean:
	rm -f *.o allocator