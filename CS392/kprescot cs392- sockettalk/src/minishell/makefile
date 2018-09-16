IDIR = ../../include
LDIR= ../../lib
CC = gcc
CFILES = $(wildcard *.c)
CFLAGS = -Wall -Werror --pedantic -I$(IDIR) -L$(LDIR) -lmy
EXECUTABLES = $(patsubst %.c,%,$(CFILES))

all:
	$(CC) $(CFILES) -o $(EXECUTABLES) $(CFLAGS) 

clean:
	rm -f *.o

fclean: clean
	rm -f $(EXECUTABLES)

re: fclean all 

