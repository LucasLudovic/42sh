/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Adding the pipe function
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "actions/execute_actions.h"
#include "builtin/builtin.h"
#include "parser/parser.h"
#include "my.h"
#include "my_macros.h"
#include "my_alloc.h"
#include "shell/my_shell.h"

static
void alloc_single_node(pipes_splits_t **pipes_split, char **arguments, int i)
{
    if (pipes_split == NULL || *pipes_split == NULL)
        return;
    if (arguments[i + 1] != NULL) {
        (*pipes_split)->next = malloc(sizeof(pipes_splits_t));
        if ((*pipes_split)->next == NULL)
            return;
        (*pipes_split)->next->arguments = &(arguments[i + 1]);
        (*pipes_split)->next->next = NULL;
        (*pipes_split)->path = NULL;
        (*pipes_split) = (*pipes_split)->next;
    }
}

static
void split_arguments(pipes_splits_t *pipes_split, char **arguments)
{
    if (pipes_split == NULL || arguments == NULL)
        return;
    for (size_t i = 0; arguments[i] != NULL; i += 1) {
        if (my_strcmp(arguments[i], "|") == 0) {
            free(arguments[i]);
            arguments[i] = NULL;
            alloc_single_node(&pipes_split, arguments, i);
        }
    }
}

pipes_splits_t *parse_pipes(char **arguments)
{
    pipes_splits_t *pipes_split = NULL;

    if (arguments == NULL || arguments[0] == NULL)
        return NULL;
    pipes_split = malloc(sizeof(pipes_splits_t));
    if (pipes_split == NULL)
        return NULL;
    pipes_split->arguments = arguments;
    pipes_split->next = NULL;
    pipes_split->path = NULL;
    split_arguments(pipes_split, arguments);
    return pipes_split;
}

static
int retrieve_stdout_and_stdin(int *save_stdout, int *save_stdin,
    shell_t *shell)
{
    if (save_stdout == NULL || save_stdin == NULL || shell == NULL)
        return FAILURE;
    dup2(*save_stdout, STDOUT_FILENO);
    close(*save_stdout);
    dup2(*save_stdin, STDIN_FILENO);
    close(*save_stdin);
    return shell->exit_status;
}

static
void execute_child(int descriptor[2], shell_t *shell, builtin_t *builtin_array,
    pipes_splits_t *pipes_arguments)
{
    if (pipes_arguments == NULL)
        return;
    close(descriptor[0]);
    dup2(descriptor[1], STDOUT_FILENO);
    close(descriptor[1]);
    execute_action(shell, builtin_array, pipes_arguments->arguments);
    exit(SUCCESS);
}

static
void execute_parent(int descriptor[2], shell_t *shell,
    builtin_t *builtin_array, pipes_splits_t *pipes_arguments)
{
    int status = SUCCESS;

    close(descriptor[1]);
    dup2(descriptor[0], STDIN_FILENO);
    close(descriptor[0]);
    execute_pipe(shell, builtin_array, pipes_arguments->next);
    waitpid(-1, &status, 0);
}

int execute_pipe(shell_t *shell, builtin_t *builtin_array,
    pipes_splits_t *pipes_arguments)
{
    pid_t current_pid = -1;
    int descriptor[2] = { 0 };
    int save_stdout = dup(STDOUT_FILENO);
    int save_stdin = dup(STDIN_FILENO);

    if (pipes_arguments == NULL)
        return shell->exit_status;
    if (pipes_arguments->next == NULL)
        return execute_action(shell, builtin_array,
            pipes_arguments->arguments);
    if (pipe(descriptor) < 0)
        return display_error("Unable to pipe\n");
    current_pid = fork();
    if (current_pid < 0)
        return display_error("Unable to fork with pipes\n");
    if (current_pid == 0)
        execute_child(descriptor, shell, builtin_array, pipes_arguments);
    else
        execute_parent(descriptor, shell, builtin_array, pipes_arguments);
    return retrieve_stdout_and_stdin(&save_stdout, &save_stdin, shell);
}
