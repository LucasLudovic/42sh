##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile for my lib
##

SRC	=	my_find_prime_sup.c \
		my_is_prime.c  \
		my_putstr.c  \
		my_showstr.c \
		my_strcapitalize.c \
		my_strcpy.c \
		my_str_isnum.c \
		my_strlen.c \
		my_strncmp.c \
		my_compute_power_rec.c \
		my_getnbr.c \
		my_putchar.c \
		my_revstr.c \
		my_show_word_array.c \
		my_strcat.c \
		my_str_isalpha.c \
		my_str_isprintable.c \
		my_strlowcase.c \
		my_strncpy.c \
		my_strupcase.c \
		my_compute_square_root.c \
		my_isneg.c \
		my_put_nbr.c \
		my_showmem.c \
		my_sort_int_array.c \
		my_strcmp.c \
		my_str_islower.c \
		my_str_isupper.c \
		my_strncat.c \
		my_strstr.c \
		my_strdup.c \
		my_swap.c \
		my_nbr_to_str.c	\
		display_error.c \
		my_str_to_word_array.c \
		my_nbr_to_str.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

all:	$(NAME)

$(NAME):
	@gcc -c $(SRC)
	@ar rc $(NAME) $(OBJ)
	@cp $(NAME) ../
	@cp my.h ../../include/

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -rf ../$(NAME)
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
