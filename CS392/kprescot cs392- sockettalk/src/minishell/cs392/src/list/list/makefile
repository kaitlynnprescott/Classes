IDIR = ../../include
CC = gcc
CFILES = $(wildcard *.c)
CFLAGS = -Wall -Werror --pedantic -I$(IDIR)
EXECUTABLES = $(patsubst %.c,%,$(CFILES))

all:
	$(CC) -c $(CFILES) $(CFLAGS) 
	ar -rc liblist.a *.o
	ranlib liblist.a
	mv liblist.a ../../lib

clean:
	rm -f *.o

fclean: clean
	rm -f $(EXECUTABLES)

re: fclean all 

