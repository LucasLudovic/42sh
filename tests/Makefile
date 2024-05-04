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
SRC	+=	../src/dependencies/update_history.c
SRC	+=	../src/shell/my_shell.c
SRC	+=	../src/shell/prompt.c
SRC	+=	../src/shell/line_editing.c
SRC	+=	../src/parser/check_ambiguity.c
SRC	+=	../src/parser/double_left_redirection.c
SRC	+=	../src/parser/double_right_redirection.c
SRC	+=	../src/parser/single_left_redirection.c
SRC	+=	../src/parser/single_right_redirection.c
SRC	+=	../src/parser/pipes.c
SRC	+=	../src/parser/semicolon.c
SRC	+=	../src/shell/pipes_handling.c
SRC	+=	../src/parser/retrieve_stdin.c
SRC	+=	../src/parser/retrieve_stdout.c
SRC	+=	../src/dependencies/set_local_variable.c
src	+=	../src/dependencies/update_history.c
SRC	+=	../src/builtin/history.c
SRC	+=	../src/dependencies/retrieve_variable.c
SRC	+=	../src/dependencies/update_return_value.c
SRC	+=	fonctionnal_tests.c

OBJ	=	$(SRC:.c=.o)

NAME	=	unit_tests

CFLAGS	=	-W -Wall -Wextra
CFLAGS	+=	-I ../include/
CFLAGS	+=	--coverage -lcriterion
CFLAGS	+=	-L ../lib -lmy -lmy_alloc

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
	@	rm -f ../$(NAME)

re:	fclean all

.PHONY:	all clean fclean re
