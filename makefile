CC = gcc
CFLAGS += -Wall -ansi

SRCS = 	main.c		\
		mm.c		\
		pc.c		\
		stdlib.c	\
		
OBJS = ${SRCS:.c=.o}
PROG = prog

.SUFFIXES:	.c .o

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

all:	$(OBJS)
	gcc -o $(PROG) $(OBJS)

clean:
	rm -f $(OBJS) $(PROG) 
#	vim: set noet:
