CC = gcc
DEBUG = -O3
LDLIBS = -lwiringPi -lwiringPiDev -lm
INCLUDE = -I.

CFLAGS = $(DEBUG) -Wall $(INCLUDE)


*.o: *.c
	$(CC) $(CFLAGS) -o $@ -c $<

drive: main.o
	$(CC) -o $@  $< $(LDLIBS)


.PHONY: clean test-drive

test-drive: drive
	sudo ./drive

clean:
	rm -f *.o drive

