CC = gcc
CFLAGS += -W -Wall -Wstrict-prototypes -ansi -pedantic -g

SRCS = 	main.c		\
		mm.c		\
		pc.c		\
		stdlib.c	\
		
OBJS = ${SRCS:.c=.o}
PROG = prog

.SUFFIXES:	.h .c .o

.h.c:
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

all:	$(OBJS)
	gcc -o $(PROG) $(OBJS)

clean:
	rm -f $(OBJS) $(PROG) 
#	vim: set noet:
