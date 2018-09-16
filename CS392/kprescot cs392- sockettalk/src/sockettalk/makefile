SNAME = server
SSRC = server.c
SOBJ = $(SSRC:.c=.o)

CNAME = client
CSRC = client.c
COBJ = $(CSRC:.c=.o)

RM = rm -f
INCLPATH = ../../include
LIBPATH = ../../lib
CFLAGS += -I $(INCLPATH)

all: client server
	
client: $(COBJ)
	cc -I ../../include -L ../../lib $(COBJ) -llist -lmy -o $(CNAME)

server: $(SOBJ)
	cc -I ../../include -L ../../lib $(SOBJ) -llist -lmy -o $(SNAME)

clean:
	-$(RM) *.o
	-$(RM) *.swp
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core
	-$(RM) *.stackdump

fclean: clean
	-$(RM) $(SNAME)
	-$(RM) $(CNAME)

re: fclean all


# NAME1 = client
# NAME2 = server

# SRC1 = client.c
# SRC2 = server.c

# OBJ1 = $(SRC:.c=.o)
# OBJ2 = $(SRC:.c=.o)

# RM = rm -f
# INCLPATH = ../../include
# LIBRARYPATH = ../../lib 
# CFLAGS += -I../../include
# LDFLAGS += -L$(LIBRARYPATH)
# LDLIBS += -lmy -lcrypto

# all:
# 	cc -L$(LIBRARYPATH) -I $(INCLPATH) client.c $(LDLIBS) -o $(NAME1)
# 	cc -L$(LIBRARYPATH) -I $(INCLPATH) server.c $(LDLIBS) -o $(NAME2)

# client: $(NAME1)
# 	cc -L$(LIBRARYPATH) -I $(INCLPATH) client.c $(LDLIBS) -o $(NAME1)

# server:  $(NAME2)
# 	cc -L$(LIBRARYPATH) -I $(INCLPATH) server.c $(LDLIBS) -o $(NAME2)

# clean:
# 	-$(RM) *.o
# 	-$(RM) *.swp
# 	-$(RM) *~
# 	-$(RM) \#*
# 	-$(RM) *.core
# 	-$(RM) *.exe
# 	-$(RM) *.exe.stackdump

# fclean: clean
# 	-$(RM) $(LIBPATH)/$(NAME1)

# re: fclean all