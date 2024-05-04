/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** File to edit the line of the input user
*/

#include <stddef.h>
#include <termio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "my.h"
#include "parser/parser.h"
#include "builtin/history.h"
#include "shell/my_shell.h"

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
void move_cursor_left(long *cursor_position, long *i)
{
    if (*i > 0) {
        *i -= 1;
        my_putstr("\033[1D");
        *cursor_position -= 1;
    }
}

static
void move_cursor_right(char *user_input, long *cursor_position, long *i)
{
    if (*i < my_strlen(user_input)) {
        *i += 1;
        my_putstr("\033[1C");
        *cursor_position += 1;
    }
}

static
void execute_escape_sequence(char *user_input, long *cursor_position,
    long *i, char c)
{
    char escape = 0;

    if (c == '\033') {
        getchar();
        escape = getchar();
        switch (escape) {
            case 'A':
                break;
            case 'B':
                break;
            case 'C':
                move_cursor_right(user_input, cursor_position, i);
                break;
            case 'D':
                move_cursor_left(cursor_position, i);
                break;
        }
    }
}

static
void update_string(char *user_input, long *i, char c)
{
    if (c == 8 || c == 127) {
        if (my_strlen(user_input) + *i > my_strlen(user_input)) {
            memmove(&user_input[*i - 1], &user_input[*i],
                strlen(user_input) - (*i - 1));
            *i -= 1;
        }
    } else {
        memmove(&user_input[*i + 1], &user_input[*i], strlen(user_input) - *i);
        user_input[*i] = c;
        *i += 1;
    }
}

static
void update_input(shell_t *shell, char *user_input, long *position[2], char c)
{
    long *cursor_position = position[0];
    long *i = position[1];

    if (c != '\033' && c != '\n' && c != EOF) {
        printf("\r\033[2K");
        fflush(stdout);
        update_string(user_input, i, c);
        print_prompt(shell);
        my_putstr(user_input);
        fflush(stdout);
        if (*cursor_position > 0)
            printf("\033[%zuC", *cursor_position);
        if (*cursor_position < 0)
            printf("\033[%zuD", *cursor_position * -1);
    }
}

static
char *retrieve_termios_input(shell_t *shell, char *user_input)
{
    long i = 0;
    char c = 'a';
    long cursor_position = 0;
    long *position[2] = { &cursor_position, &i };

    while (c != '\n' && c != EOF) {
        c = getchar();
        execute_escape_sequence(user_input, &cursor_position, &i, c);
        update_input(shell, user_input, position, c);
    }
    return user_input;
}

static
char *execute_line_editor(shell_t *shell)
{
    struct termios old_termios = { 0 };
    struct termios new_termios = { 0 };
    char *user_input = malloc(sizeof(char) * 10000);

    if (user_input == NULL)
        return NULL;
    memset(user_input, '\0', sizeof(char) * 10000);
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
    user_arguments = parse_semicolon(user_input);
    free(user_input);
    return user_arguments;
}
