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
#include "builtin/set_variables.h"
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
#include "shell/my_shell.h"
#include "dependencies/set_local_variable.h"
#include "dependencies/initialize_builtins.h"

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
    if (shell != NULL && shell->variable != NULL)
        free_local_variable(shell->variable);
    if (builtin_array == NULL)
        return;
    for (int i = 0; i < 8; i += 1) {
        if (builtin_array->name[i] != NULL)
            free(builtin_array->name[i]);
    }
}

int check_if_tty(void)
{
    struct stat terminal = { 0 };

    fstat(0, &terminal);
    if (S_ISFIFO(terminal.st_mode)) {
        return TRUE;
    }
    return FALSE;
}

int check_redirection(char **every_arguments, char *arguments,
    int *fd, int *input_fd)
{
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
    comparison_t *comparison = NULL;
    comparison_t *head = NULL;
    char **split_arguments = NULL;
    pipes_splits_t *pipes_split = NULL;
    int output_fd = STDOUT_FILENO;
    int input_fd = STDIN_FILENO;
    int save_stdout = 0;
    int save_input = 0;

    for (size_t i = 0; arguments[i] != NULL; i += 1) {
        comparison = retrieve_and_or_operator(my_shell, my_strdup(arguments[i]));
        head = comparison;
        while (comparison != NULL) {
            if (comparison->previous_comparator == AND && my_shell->exit_status != 0)
                break;
            if (comparison->previous_comparator == OR && my_shell->exit_status == 0)
                break;
            if (check_redirection(arguments, comparison->argument,
                &output_fd, &input_fd) == FAILURE)
                return;
            split_arguments = my_str_to_word_array(comparison->argument);
            retrieve_variable(my_shell, split_arguments);
            assign_output_input(output_fd, input_fd, &save_stdout, &save_input);
            pipes_handling(my_shell, builtin_array, split_arguments, &pipes_split);
            retrieve_stdout(&output_fd, &save_stdout);
            retrieve_stdin(&input_fd, &save_input);
            update_return_value(my_shell);
            destroy_pipes_split(pipes_split);
            comparison = comparison->next;
        }
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
