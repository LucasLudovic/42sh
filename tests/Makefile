##
## EPITECH PROJECT, 2023
## make create
## File description:
## make
##

SRC	=	../src/attack.c
SRC	+=	../src/connection.c
SRC	+=	../src/defense.c
SRC	+=	../src/gameboard.c
SRC	+=	../src/gameloop.c
SRC	+=	../src/my_navy.c
SRC	+=	../src/transform_map.c
SRC	+=	../src/retrieve_info.c
SRC	+=	test_transform_map.c
SRC	+=	test_info.c

OBJ	=	$(SRC:.c=.o)

NAME	=	unit_tests

CFLAGS	=	-W -Wall -Wextra
CFLAGS	+=	-I ../include/
CFLAGS	+=	--coverage -lcriterion
CFLAGS	+=	-L ../lib/my -lmy

CC	=	gcc -g3

all:	$(NAME)

$(NAME)	:	$(OBJ)
	@	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)
	@	mv $(NAME) ../

clean:
	@	rm -f $(OBJ)
	@	rm -f ../*.o

fclean:	clean
	@	rm -f $(NAME)
	@	rm -f ../src/*.gcno
	@	rm -f ../src/*.gcda
	@	rm -f *.gcno
	@	rm -f *.gcda
	@	rm -f ../$(NAME)

re:	fclean all

.PHONY:	all clean fclean re
