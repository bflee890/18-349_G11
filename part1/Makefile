CC      = gcc
CFLAGS  = -g -O2 -Wall -Werror
ASFLAGS = -g

objects = part1-main.o part1-strTable.o

default: part1

.PHONY: default clean clobber

part1: $(objects)
	$(CC) -g -o $@ $^

part1-main.o: part1-main.c
part1-strTable.o: part1-strTable.s

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.s
	$(CC) -c $(ASFLAGS) -o $@ $<

clean:
	rm -f $(objects)

clobber: clean
	rm -f part1
