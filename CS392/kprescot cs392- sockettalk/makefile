CC = gcc
FILES = my_strfind.c my_strrfind.c my_strcmp.c my_strncmp.c my_strcpy.c my_strncpy.c my_strcat.c my_strdup.c my_strconcat.c my_strnconcat.c my_atoi.c
OUT_EXE = homework2
CFLAGS = -Wall -Werror --pedantic
OBJ = $(FILES:.c=.o)

all: $(FILES)
	$(CC) $(CFLAGS) -c $(FILES)
	ar -rc libmy.a *.o
	ranlib libmy.a
	mv libmy.a ../../lib


clean:
	-$(RM) *.o

flcean:
	clean
	-$(RM) OUT_EXE

re:
	flcean all
