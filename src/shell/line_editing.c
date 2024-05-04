/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** File to edit the line of the input user
*/

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
char *execute_line_editor(shell_t *shell)
{
    struct termios old_termios, new_termios;
    char *user_input = malloc(sizeof(char) * 10000);
    size_t i = 0;
    char c = 'a';
    int cursor_position = 0;

    if (user_input == NULL)
        return NULL;
    memset(user_input,'\0', sizeof(char) * 10000);
    tcgetattr(0, &old_termios);
    new_termios = old_termios;  
    new_termios.c_lflag &= ~ICANON; 
    new_termios.c_lflag &= ~ECHO; 
    tcsetattr(0, TCSANOW, &new_termios); 
    while (c != '\n' && c != EOF) {
        c = getchar();
        if (c == '\033') {
            getchar();
            switch(getchar()) {
                case 'A':
                    break;
                case 'B':
                    break;
                case 'C':
                    if(i < strlen(user_input)) {
                        i += 1;
                        my_putstr("\033[1C");
                        cursor_position += 1;
                    }
                    break;
                case 'D':
                    if(i > 0) {
                        i -= 1;
                        my_putstr("\033[1D");
                        cursor_position -= 1;
                    }
                    break;
            }
        } else {
            if (c == '\n' || c == EOF)
                break;
            printf("\r\033[2K");
            fflush(stdout);
            if (c == 8 || c == 127) // replace by macro later
            {
                if (strlen(user_input) > 0) {
                    memmove(&user_input[i - 1], &user_input[i], strlen(user_input) - (i - 1));
                    i -= 1;
                }
            }
            else {
                memmove(&user_input[i + 1], &user_input[i], strlen(user_input) - i);
                user_input[i] = c;
                i += 1;
            }
            if (!check_if_tty())
                print_prompt(shell);
            my_putstr(user_input);
            fflush(stdout);
            if (cursor_position > 0)
                printf("\033[%dC", cursor_position);
            if (cursor_position < 0)
                printf("\033[%dD", cursor_position * -1);
        }
    }
    my_putstr("\n");
    tcsetattr(0, TCSANOW, &old_termios);   
    return user_input;
}

char **get_user_arguments(shell_t *shell, char **user_arguments)
{
    char *user_input = NULL;

    if (!check_if_tty())
        user_input = execute_line_editor(shell);
    else {
        return NULL;
    }
    update_history(shell, user_input);
    user_arguments = parse_semicolon(user_input);
    free(user_input);
    return user_arguments;
}
