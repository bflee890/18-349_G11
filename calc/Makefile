CC     = gcc
CFLAGS = -O2 -Wall -Werror

objects = math.o calc.o

calc: $(objects)
	$(CC) -o $@ $^

math.o: math.c math.h
calc.o: calc.c math.h

%.o: %.c $.h
	$(CC) -c $(CFLAGS) $@ $<

clean:
	rm -f $(objects)
 
clobber: clean
	rm -f calc
