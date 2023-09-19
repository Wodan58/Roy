#
#   module  : makefile
#   version : 1.2
#   date    : 09/19/23
#
PROG   = fib
.PRECIOUS: $(PROG).c
.POSIX:
.SUFFIXES:
.SUFFIXES: .c .o .joy

CC     = gcc
CFLAGS = -DTRACING -O3 -Wall -Wextra -Werror -Wno-unused-parameter
HDRS   = globals.h
OBJS   = $(PROG).o exeterm.o ersatz.o main.o exec.o writ.o

$(PROG):	prep $(OBJS)
	$(CC) -o$@ $(OBJS) -lm -lgc

$(OBJS): $(HDRS)

prep:
	sh prim.sh .
	sh defs.sh .
	sh deps.sh .

.c.o:
	$(CC) -o$@ $(CFLAGS) -c $<

.joy.c:
	./joy -c $<

clean:
	rm -f *.o $(PROG).c