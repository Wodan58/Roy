#
#   module  : makefile
#   version : 1.3
#   date    : 10/02/23
#
PROG   = fib
.PRECIOUS: $(PROG).c
.POSIX:
.SUFFIXES:
.SUFFIXES: .c .o .joy

CC     = gcc
CFLAGS = -O3 -Wall -Wextra -Werror -Wno-unused-parameter
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
	rm -f *.o defs.h deps.h prim.c prim.h
