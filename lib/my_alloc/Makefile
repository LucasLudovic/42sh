##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile for my lib
##

SRC	=	my_alloc.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy_alloc.a

all:	$(NAME)

$(NAME):
	@gcc -g3 -c $(SRC)
	@ar rc $(NAME) $(OBJ)
	@cp $(NAME) ../
	@cp my_alloc.h ../../include/

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -rf ../$(NAME)
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
