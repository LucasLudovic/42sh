##
## EPITECH PROJECT, 2023
## make create
## File description:
## make
##

SRC	=	../src/actions/execute_actions.c
SRC	+=	../src/builtin/alias.c
SRC	+=	../src/builtin/cd.c
SRC	+=	../src/builtin/env.c
SRC	+=	../src/builtin/exit.c
SRC	+=	../src/builtin/setenv.c
SRC	+=	../src/builtin/unsetenv.c
SRC	+=	../src/dependencies/environment_array.c
SRC	+=	../src/dependencies/get_environment.c
SRC	+=	../src/dependencies/which.c
SRC	+=	../src/shell/my_shell.c
SRC	+=	../src/shell/prompt.c
SRC	+=	actions/tests_execute_actions.c

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
	@	find .. -name *.gcno -delete
	@	find .. -name *.gcda -delete
	@	rm -f ../$(NAME)

re:	fclean all

.PHONY:	all clean fclean re
