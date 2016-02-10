OBJS = main.o queue.o heap.o
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

12bit : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o 12bit

main.o : common.h queue.h heap.h main.c
	$(CC) $(CFLAGS) main.c

queue.o : common.h queue.h queue.c
	$(CC) $(CFLAGS) queue.c

heap.o : common.h heap.h heap.c
	$(CC) $(CFLAGS) heap.c

clean:
	\rm *.o *out 12bit
