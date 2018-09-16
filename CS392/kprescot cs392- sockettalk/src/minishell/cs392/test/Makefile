CC = gcc
IDIR = ../../include
LDIR = ../../lib
CFLAGS = -I$(IDIR) -g -std=c99 -Wall -Werror -pedantic
LDLIBS = -L$(LDIR) -lmy

check: testmy
	./testmy

clean:
	-rm -f ./testmy
