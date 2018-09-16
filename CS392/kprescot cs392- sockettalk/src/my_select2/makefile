NAME = my_select
SRC = my_select.c print_args.c changed_window.c
OBJ = $(SRC:.c=.o)
RM = rm -f

all:
	gcc -o $(NAME) $(SRC) -lncurses

clean:
	-$(RM) *.o
	-$(RM) *.swp
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core
	-$(RM) *.exe
	-$(RM) *.exe.stackdump

fclean: clean
	-$(RM) $(LIBPATH)/$(NAME)

re: clean all 