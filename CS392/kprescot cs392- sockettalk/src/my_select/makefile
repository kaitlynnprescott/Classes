NAME = my_select
SRC = my_select.c start_term.c setup_elements.c restore_term.c \
quit_term.c clear_term.c get_cap.c initialize_termcaps.c \
my_termprint.c up.c down.c left.c right.c select_element.c show_elements.c \
char_check.c move_next.c highlight_on.c highlight_off.c underline_on.c \
underline_off.c underline_refresh.c no_underline_refresh.c 
OBJ = $(SRC:.c=.o)
RM = rm -f

INCLPATH = ../../include
LIBPATH = ../../lib 
CFLAGS += -I$(INCLPATH)
LDFLAGS += -L$(LIBPATH)
LDLIBS += -lmy -ltermcap

all: $(NAME)

$(NAME): $(OBJ)

clean:
	-$(RM) *.o
	-$(RM) *.swp
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core

fclean: clean
	-$(RM) $(NAME)

re: clean all 