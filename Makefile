FILE = tools.c

SRCCLIENT	=	client.c $(FILE)
SRCSERVER	=	server.c $(FILE)

OBJ_C	= $(SRCCLIENT:.c=.o)
OBJ_S	=	$(SRCSERVER:.c=.o)

CC			=	gcc
CFLAG		=	-Wall -Wextra -Werror
RM			=	rm -rf

NAME_C	=	client
NAME_S	=	server

all: $(NAME_C) $(NAME_S)

$(NAME_C): $(OBJ_C)
	$(CC) $(CFLAG) $(OBJ_C) -o $(NAME_C)

$(NAME_S): $(OBJ_S)
	$(CC) $(CFLAG) $(OBJ_S) -o $(NAME_S)

clean:
	$(RM) $(OBJ_C) $(OBJ_S)

fclean: clean
	$(RM) $(NAME_C) $(NAME_S)

re: fclean all

.PHONY: clean fclean re