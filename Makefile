##
## EPITECH PROJECT, 2018
## mychap
## File description:
## Makefile
##

CC			=	gcc
INC			=	-Iinclude/
DSRC		=	src/

SRC			=	$(DSRC)main.c			\

CFLAGS		+=	-Wall -Wextra $(INC)
OBJ			=	$(SRC:.c=.o)
NAME		=	client

all: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_UT)

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug