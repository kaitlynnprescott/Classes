CC = gcc
FILES = my_alpha.c my_atoi.c my_char.c my_digits.c my_int.c my_num_base.c my_revstr.c my_str.c my_str2vect.c my_strcat.c my_strcmp.c my_strconcat.c my_strcpy.c my_strdup.c my_strfind.c my_strindex.c my_strlen.c my_strncmp.c my_strnconcat.c my_strncpy.c my_strrfind.c my_strrindex.c my_vect2str.c my_malloc.c
OUT_EXE = homework2
CFLAGS = -Wall -Werror --pedantic -I../../include
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
