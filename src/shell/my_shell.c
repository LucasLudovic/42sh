/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_shell
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <termio.h>
#include "dependencies/environment.h"
#include "dependencies/history_struct.h"
#include "builtin/builtin.h"
#include "builtin/env.h"
#include "builtin/setenv.h"
#include "builtin/unsetenv.h"
#include "builtin/exit.h"
#include "builtin/cd.h"
#include "builtin/alias.h"
#include "builtin/history.h"
#include "parser/parser.h"
#include "actions/execute_actions.h"
#include "shell/my_shell.h"
#include "my_alloc.h"
#include "my.h"
#include "my_macros.h"
#include "parser/retrieve_stdin.h"
#include "parser/retrieve_stdout.h"
#include "shell/pipes_handling.h"
#include "dependencies/set_local_variable.h"

static
void destroy_end(shell_t *shell, environment_t **shell_environment,
    builtin_t *builtin_array)
{
    if (shell != NULL) {
        shell->alias = destroy_alias(shell->alias);
        destroy_history(shell->history);
    }
    if (shell != NULL && shell->previous_path != NULL)
        free(shell->previous_path);
    destroy_environment_list(shell_environment);
    if (builtin_array == NULL)
        return;
    for (int i = 0; i < 7; i += 1) {
        if (builtin_array->name[i] != NULL)
            free(builtin_array->name[i]);
    }
}

static
int check_if_tty(void)
{
    struct stat terminal = { 0 };

    fstat(0, &terminal);
    if (S_ISFIFO(terminal.st_mode)) {
        return TRUE;
    }
    return FALSE;
}

static
int initialize_function_pointer_array(builtin_t *builtin_array)
{
    builtin_array->name[0] = my_strdup("env");
    builtin_array->function[0] = &env;
    builtin_array->name[1] = my_strdup("setenv");
    builtin_array->function[1] = &my_setenv;
    builtin_array->name[2] = my_strdup("unsetenv");
    builtin_array->function[2] = &my_unsetenv;
    builtin_array->name[3] = my_strdup("exit");
    builtin_array->function[3] = &exit_shell;
    builtin_array->name[4] = my_strdup("cd");
    builtin_array->function[4] = &change_directory;
    builtin_array->name[5] = my_strdup("alias");
    builtin_array->function[5] = &replace_alias;
    builtin_array->name[6] = my_strdup("history");
    builtin_array->function[6] = &history;
    if (builtin_array->name[0] == NULL || builtin_array->name[1] == NULL ||
        builtin_array->name[2] == NULL || builtin_array->name[3] == NULL ||
        builtin_array->name[4] == NULL || builtin_array->name[5] == NULL ||
        builtin_array->name[6] == NULL)
        return FAILURE;
    return SUCCESS;
}

static
char **get_user_arguments(shell_t *shell, char **user_arguments)
{
    struct termios old_termios, new_termios;
    char *user_input = malloc(sizeof(char) * 10000);
    memset(user_input,'\0', sizeof(char) * 10000);
    size_t i = 0;
    char c = 'a';
    int cursor_position = 0;

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
    update_history(shell, user_input);
    user_arguments = parse_semicolon(user_input);
    free(user_input);
    return user_arguments;
}

static
int check_redirection(char **every_arguments, char *arguments,
    int *fd, int *input_fd)
{
    if (every_arguments == NULL)
        return FAILURE;
    if (check_ambiguity(every_arguments) == TRUE)
        return FAILURE;
    if (arguments == NULL || fd == NULL)
        return FAILURE;
    for (size_t j = 0; arguments[j] != '\0'; j += 1) {
        if (arguments[j] == '<' && arguments[j + 1] == '<')
            parse_double_left_redirection(&arguments[j]);
        if (arguments[j] == '>' && arguments[j + 1] == '>')
            parse_double_right_redirection(arguments, fd);
        if (arguments[j] == '>' && arguments[j + 1] != '>')
            parse_single_right_redirection(arguments, fd);
        if (arguments[j] == '<' && arguments[j + 1] != '<')
            parse_single_left_redirection(arguments, input_fd);
    }
    return SUCCESS;
}

static
void destroy_pipes_split(pipes_splits_t *pipes_split)
{
    pipes_splits_t *tmp = NULL;

    if (pipes_split == NULL)
        return;
    while (pipes_split != NULL) {
        tmp = pipes_split;
        pipes_split = pipes_split->next;
        free(tmp);
    }
}

static void assign_output_input(int output_fd, int
    input_fd, int *save_stdout, int *save_input)
{
    (*save_stdout) = dup(STDOUT_FILENO);
    dup2(output_fd, STDOUT_FILENO);
    (*save_input) = dup(STDIN_FILENO);
    dup2(input_fd, STDIN_FILENO);
}

static
void execute_single_instruction(char **arguments, shell_t *my_shell,
    builtin_t *builtin_array)
{
    char **split_arguments = NULL;
    pipes_splits_t *pipes_split = NULL;
    int output_fd = STDOUT_FILENO;
    int input_fd = STDIN_FILENO;
    int save_stdout = 0;
    int save_input = 0;

    if (arguments == NULL || arguments[0] == NULL)
        return;
    for (size_t i = 0; arguments[i] != NULL; i += 1) {
        if (check_redirection(arguments, arguments[i],
            &output_fd, &input_fd) == FAILURE)
            return;
        split_arguments = my_str_to_word_array(arguments[i]);
        assign_output_input(output_fd, input_fd, &save_stdout, &save_input);
        pipes_handling(my_shell, builtin_array, split_arguments, &pipes_split);
        retrieve_stdout(&output_fd, &save_stdout);
        retrieve_stdin(&input_fd, &save_input);
        destroy_pipes_split(pipes_split);
    }
}

static void initialize_dependencies(shell_t *shell, char **environment)
{
    if (shell == NULL || environment == NULL || *environment == NULL)
        return;
    shell->environment = get_environment(environment);
    set_local_variable(shell);
}

int my_shell(char **environment)
{
    shell_t shell = { .alive = TRUE, .environment = NULL, .history = NULL,
        .exit_status = SUCCESS, .previous_path = NULL, .alias = NULL,
        .variable = NULL};
    builtin_t builtin_array = { 0 };
    char **arguments = NULL;

    if (initialize_function_pointer_array(&builtin_array) == FAILURE)
        return FAILURE;
    initialize_dependencies(&shell, environment);
    while (shell.alive) {
        if (!check_if_tty())
            print_prompt(&shell);
        arguments = get_user_arguments(&shell, arguments);
        if (arguments == NULL || arguments[0] == NULL)
            break;
        execute_single_instruction(arguments, &shell, &builtin_array);
        destroy_user_arguments(arguments);
    }
    destroy_end(&shell, &shell.environment, &builtin_array);
    return shell.exit_status;
}
