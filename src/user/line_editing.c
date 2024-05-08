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
void refresh_input(shell_t *shell, char *user_input, long *cursor_position)
{
    printf("\r\033[2K");
    fflush(stdout);
    print_prompt(shell);
    my_putstr(user_input);
    fflush(stdout);
    if (*cursor_position > 0)
        printf("\033[%zuC", *cursor_position);
    if (*cursor_position < 0)
        printf("\033[%zuD", *cursor_position * -1);
}

static
void retrieve_history_up(shell_t *shell, char *user_input,
    long *cursor_position, long *i)
{
    if (shell->history == NULL || user_input == NULL)
        return;
    while (shell->history != NULL) {
        if (shell->history == NULL)
            return;
        if (strncmp(shell->current_input, shell->history->cmd,
            strlen(shell->current_input)) == 0
            && (strcmp(user_input, shell->history->cmd) != 0)) {
            *i = strlen(shell->history->cmd);
            my_strcpy(user_input, shell->history->cmd);
            refresh_input(shell, user_input, cursor_position);
            if (shell->history->next != NULL)
                shell->history = shell->history->next;
            break;
        }
        if (shell->history->next == NULL)
            break;
        shell->history = shell->history->next;
    }
}

static
void retrieve_history_down(shell_t *shell, char *user_input,
    long *cursor_position, long *i)
{
    if (shell->history == NULL || user_input == NULL)
        return;
    while (shell->history != NULL) {
        if (shell->history == NULL)
            return;
        if (strncmp(shell->current_input, shell->history->cmd,
            strlen(shell->current_input)) == 0
            && (strcmp(user_input, shell->history->cmd) != 0)) {
            *i = strlen(shell->history->cmd);
            my_strcpy(user_input, shell->history->cmd);
            refresh_input(shell, user_input, cursor_position);
            if (shell->history->prev != NULL)
                shell->history = shell->history->prev;
            break;
        }
        if (shell->history->prev == NULL)
            break;
        shell->history = shell->history->prev;
    }
}

static
void get_escape(shell_t *shell, char *user_input,
    long *position[2], char escape)
{
    long *cursor_position = position[0];
    long *i = position[1];

    switch (escape) {
        case 'A':
            retrieve_history_up(shell, user_input, cursor_position, i);
            break;
        case 'B':
            retrieve_history_down(shell, user_input, cursor_position, i);
            break;
        case 'C':
            move_cursor_right(user_input, cursor_position, i);
            break;
        case 'D':
            move_cursor_left(cursor_position, i);
            break;
    }
}

static
void update_string(shell_t *shell, char *user_input, long *i, char c)
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
    if (user_input != NULL) {
        if (shell->current_input != NULL) {
            free(shell->current_input);
            shell->current_input = NULL;
        }
        shell->current_input = my_strdup(user_input);
    }
}

void execute_escape_sequence(shell_t *shell, char *user_input,
    long *position[2], char c)
{
    char escape = 0;

    if (c == '\033') {
        getchar();
        escape = getchar();
        get_escape(shell, user_input, position, escape);
    }
}

void update_input(shell_t *shell, char *user_input, long *position[2], char c)
{
    long *cursor_position = position[0];
    long *i = position[1];

    if (c != '\033' && c != '\n' && c != EOF) {
        printf("\r\033[2K");
        fflush(stdout);
        update_string(shell, user_input, i, c);
        print_prompt(shell);
        my_putstr(user_input);
        fflush(stdout);
        if (*cursor_position > 0)
            printf("\033[%zuC", *cursor_position);
        if (*cursor_position < 0)
            printf("\033[%zuD", *cursor_position * -1);
        shell->history = shell->history_head;
    }
}
