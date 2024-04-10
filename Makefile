##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile for my lib
##

SRC	=	src/main.c
SRC	+=	src/shell/my_shell.c
SRC	+=	src/shell/prompt.c
SRC	+=	src/dependencies/which.c
SRC	+=	src/dependencies/get_environment.c
SRC	+=	src/dependencies/environment_array.c
SRC	+=	src/builtin/alias.c
SRC	+=	src/builtin/env.c
SRC	+=	src/builtin/setenv.c
SRC	+=	src/builtin/unsetenv.c
SRC	+=	src/builtin/exit.c
SRC	+=	src/builtin/cd.c
SRC	+=	src/parser/semicolon.c
SRC	+=	src/parser/pipes.c
SRC	+=	src/parser/double_left_redirection.c
SRC	+=	src/parser/double_right_redirection.c
SRC	+=	src/parser/single_right_redirection.c
SRC	+=	src/parser/check_ambiguity.c
SRC	+=	src/actions/execute_actions.c

OBJ	=	$(SRC:.c=.o)

NAME	=	42sh

CC	=	gcc

CFLAGS	=	-W -Wall -Wextra -Wpedantic -g

CPPFLAGS	=	-I include

LDFLAGS	=	-L lib -lmy -lmy_alloc

all:	$(NAME)

$(NAME):	$(OBJ)
	@make -C lib/my
	@make clean -C lib/my
	@make -C lib/my_alloc
	@make clean -C lib/my_alloc
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@make fclean -C lib/my
	@make fclean -C lib/my_alloc
	@make fclean -C tests/
	@rm -f $(NAME)

re: fclean all

tests_run:	re
	@make re -C tests/
	@make clean -C tests/
	@./unit_tests
	@gcovr --exclude tests/ --exclude src/main.c
	@gcovr --exclude tests/ --exclude src/main.c --branches

.PHONY:	clean fclean re all tests_run
