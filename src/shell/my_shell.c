/*
** EPITECH PROJECT, 2024
** Main
** File description:
** Shell for the minishell project
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "dependencies/environment.h"
#include "builtin/builtin.h"
#include "builtin/env.h"
#include "builtin/setenv.h"
#include "builtin/unsetenv.h"
#include "builtin/exit.h"
#include "builtin/cd.h"
#include "parser/parser.h"
#include "actions/execute_actions.h"
#include "shell/my_shell.h"
#include "my.h"
#include "my_macros.h"

static
void destroy_end(shell_t *shell, environment_t **shell_environment,
    builtin_t *builtin_array)
{
    if (shell != NULL && shell->previous_path != NULL)
        free(shell->previous_path);
    destroy_environment_list(shell_environment);
    if (builtin_array == NULL)
        return;
    for (int i = 0; i < 5; i += 1) {
        if (builtin_array->name[i] != NULL)
            free(builtin_array->name[i]);
    }
}

static
void destroy_user_arguments(char **user_arguments)
{
    if (user_arguments == NULL)
        return;
    for (size_t i = 0; user_arguments[i] != NULL; i += 1)
        free(user_arguments[i]);
    free(user_arguments);
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
    if (builtin_array->name[0] == NULL || builtin_array->name[1] == NULL ||
        builtin_array->name[2] == NULL || builtin_array->name[3] == NULL ||
        builtin_array->name[4] == NULL)
        return FAILURE;
    return SUCCESS;
}

static
char **get_user_arguments(shell_t *shell, char **user_arguments)
{
    char *user_input = NULL;
    size_t size = 0;

    if (getline(&user_input, &size, stdin) <= 0) {
        if (user_input != NULL)
            free(user_input);
        if (check_if_tty())
            shell->alive = FALSE;
        return NULL;
    }
    if (user_input == NULL)
        return NULL;
    user_arguments = parse_semicolon(user_input);
    free(user_input);
    return user_arguments;
}

static
char *check_redirection(char *arguments, int *fd)
{
    if (arguments == NULL || fd == NULL)
        return NULL;
    for (size_t j = 0; arguments[j] != '\0'; j += 1) {
        if (arguments[j] == '<' && arguments[j + 1] == '<')
            parse_double_left_redirection(arguments);
        if (arguments[j] == '>' && arguments[j + 1] == '>')
            parse_double_right_redirection(arguments, fd);
    }
    return arguments;
}

static
void execute_single_instruction(char **arguments, shell_t *my_shell,
    builtin_t *builtin_array)
{
    char **split_arguments = NULL;
    int output_fd = STDOUT_FILENO;
    int save_stdout = 0;

    for (size_t i = 0; arguments[i] != NULL; i += 1) {
        check_redirection(arguments[i], &output_fd);
        split_arguments = my_str_to_word_array(arguments[i]);
        if (output_fd != STDOUT_FILENO) {
            save_stdout = dup(STDOUT_FILENO);
            dup2(output_fd, STDOUT_FILENO);
        }
        execute_action(my_shell, builtin_array, split_arguments);
        destroy_user_arguments(split_arguments);
        if (output_fd != STDOUT_FILENO) {
            dup2(save_stdout, STDOUT_FILENO);
            close(output_fd);
            close(save_stdout);
        }
    }
}

int my_shell(char **environment)
{
    shell_t my_shell = { .alive = TRUE, .environment = NULL,
        .exit_status = SUCCESS, .previous_path = NULL, .alias = NULL };
    builtin_t builtin_array = { 0 };
    char **arguments = NULL;

    if (initialize_function_pointer_array(&builtin_array) == FAILURE)
        return FAILURE;
    my_shell.environment = get_environment(environment);
    while (my_shell.alive) {
        if (!check_if_tty())
            print_prompt(&my_shell);
        arguments = get_user_arguments(&my_shell, arguments);
        if (arguments == NULL || arguments[0] == NULL)
            continue;
        execute_single_instruction(arguments, &my_shell, &builtin_array);
        destroy_user_arguments(arguments);
    }
    destroy_end(&my_shell, &my_shell.environment, &builtin_array);
    return my_shell.exit_status;
}
