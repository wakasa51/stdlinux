CFLAGS= -g -Wall -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

program: $(OBJS)
	gcc -o program $(OBJS)

run : program
	./program ${ARG}

clean :
	rm -f ./program *.o

.PHONY : run clean
