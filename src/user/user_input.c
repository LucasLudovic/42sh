/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Retrieve the user input
*/

#include <stddef.h>
#include <termio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "builtin/alias.h"
#include "my.h"
#include "parser/parser.h"
#include "builtin/history.h"
#include "shell/my_shell.h"
#include "user/user.h"

static
char *retrieve_termios_input(shell_t *shell, char *user_input)
{
    long i = 0;
    char c = 'a';
    long cursor_position = 0;
    long *position[2] = { &cursor_position, &i };

    shell->history_head = shell->history;
    while (c != '\n' && c != EOF) {
        c = getchar();
        execute_escape_sequence(shell, user_input, position, c);
        update_input(shell, user_input, position, c);
    }
    shell->history = shell->history_head;
    return user_input;
}

static
void initialize_termios(struct termios *old_termios,
    struct termios *new_termios)
{
    tcgetattr(0, old_termios);
    *new_termios = *old_termios;
    new_termios->c_lflag &= ~ICANON;
    new_termios->c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, new_termios);
}

static
char *execute_line_editor(shell_t *shell)
{
    struct termios old_termios = { 0 };
    struct termios new_termios = { 0 };
    char *user_input = malloc(sizeof(char) * INPUT_MAX);

    if (shell == NULL || user_input == NULL)
        return NULL;
    memset(user_input, '\0', sizeof(char) * INPUT_MAX);
    initialize_termios(&old_termios, &new_termios);
    user_input = retrieve_termios_input(shell, user_input);
    my_putstr("\n");
    tcsetattr(0, TCSANOW, &old_termios);
    return user_input;
}

static
char *get_tty_input(shell_t *shell)
{
    char *user_input = NULL;
    size_t size = 0;

    if (getline(&user_input, &size, stdin) <= 0) {
        if (user_input != NULL)
            free(user_input);
        shell->alive = FALSE;
        return NULL;
    }
    if (user_input == NULL)
        return NULL;
    if (user_input[my_strlen(user_input) - 1] == '\n')
        user_input[my_strlen(user_input) - 1] = '\0';
    return user_input;
}

char **get_user_arguments(shell_t *shell, char **user_arguments)
{
    char *user_input = NULL;

    if (!check_if_tty())
        user_input = execute_line_editor(shell);
    else
        user_input = get_tty_input(shell);
    update_history(shell, user_input);
    if (user_input == NULL)
        return NULL;
    for (size_t i = 0; user_input[i] != '\0'; i += 1) {
        user_input[i] = (user_input[i] == '#') ? '\0' : user_input[i];
    }
    use_alias(shell, &user_input);
    user_arguments = parse_semicolon(user_input);
    if (shell->current_input != NULL) {
        free(shell->current_input);
        shell->current_input = NULL;
    }
    free(user_input);
    return user_arguments;
}
