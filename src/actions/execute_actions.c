/*
** EPITECH PROJECT, 2024
** Actions
** File description:
** Execute the actions for the minishell project
*/

#include <signal.h>
#include <stdlib.h>
#include <dirent.h>
#include <threads.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "my_alloc.h"
#include "dependencies/which.h"
#include "dependencies/environment.h"
#include "builtin/builtin.h"
#include "builtin/alias.h"
#include "parser/parser.h"
#include "my_macros.h"
#include "my.h"
#include "actions/execute_actions.h"
#include "shell/pipes_handling.h"

static
int display_error_message(shell_t *shell, char *binary_name, int status)
{
    if (shell != NULL)
        shell->exit_status = (status >= 256) ? status / 256 : status;
    if (shell->exit_status == 1) {
        if (is_executable(binary_name) == false) {
            display_error(binary_name);
            display_error(": Permission denied.\n");
            return 1;
        }
    }
    if (shell->exit_status == 84) {
        display_error(binary_name);
        display_error(": Permission denied.\n");
        shell->exit_status = 1;
        return 1;
    }
    return SUCCESS;
}

static
int handle_segfault(int wait_status)
{
    int signal_number = 0;

    if (WIFSIGNALED(wait_status)) {
        signal_number = WTERMSIG(wait_status);
        if (signal_number == SIGSEGV) {
            display_error("Segmentation fault");
            check_dump(wait_status);
            return 128 + WTERMSIG(wait_status);
        }
        if (signal_number == SIGFPE) {
            display_error("Floating exception\n");
            check_dump(wait_status);
            return 128 + WTERMSIG(wait_status);
        }
    }
    return 0;
}

static
int execute_binary(shell_t *shell, char *path, char **arguments)
{
    pid_t current_pid = 0;
    char **environment_array = NULL;
    int wait_status = 0;

    environment_array = convert_environment_to_array(shell->environment);
    if (access(path, X_OK) != 0 || environment_array == NULL) {
        destroy_environment_array(environment_array);
        return display_error_message(shell, arguments[0], 1);
    }
    current_pid = fork();
    if (current_pid == 0) {
        execve(path, arguments, environment_array);
        exit(FAILURE);
    } else {
        waitpid(-1, &wait_status, 0);
        handle_segfault(wait_status);
    }
    destroy_environment_array(environment_array);
    return display_error_message(shell, arguments[0], wait_status);
}

static
int check_current_directory(char *file_name)
{
    DIR *directory = opendir(".");
    struct dirent *file = NULL;

    if (directory == NULL) {
        display_error("Can't open the current directory\n");
        return FALSE;
    }
    file = readdir(directory);
    while (file != NULL) {
        if (my_strcmp(file_name, file->d_name) == 0) {
            closedir(directory);
            return TRUE;
        }
        file = readdir(directory);
    }
    closedir(directory);
    return FALSE;
}

static
int check_as_absolute(char *file_name)
{
    if (access(file_name, F_OK) == 0)
        return TRUE;
    return FALSE;
}

static
int execute_from_current_directory(shell_t *shell, char *binary_name,
    char **arguments)
{
    if (arguments == NULL || binary_name == NULL)
        return FAILURE;
    if (my_strncmp(binary_name, "./", 2) == 0)
        binary_name += 2;
    if (!check_current_directory(binary_name) &&
        !check_as_absolute(binary_name)) {
        return FAILURE;
        }
    return execute_binary(shell, binary_name, arguments);
}

static
void check_absolute_path(shell_t *shell, char **arguments, char *binary_name)
{
    if (my_str_isprintable(binary_name) &&
        my_strlen(binary_name) > 0 && binary_name[0] != '\n') {
        shell->exit_status = 1;
        display_error(arguments[0]);
        display_error(": Command not found.\n");
    }
}

static
int execute_from_path(shell_t *shell, char *binary_name,
    char **arguments)
{
    char *binary_absolute_path = NULL;
    int status = 0;

    if (shell == NULL || arguments == NULL)
        return FAILURE;
    if (arguments[0] == NULL || my_strlen(arguments[0]) <= 0 ||
        my_str_isprintable(arguments[0]) == FALSE)
        return FAILURE;
    binary_absolute_path = get_function_absolute_path(shell->environment,
        arguments);
    if (binary_absolute_path == NULL) {
        check_absolute_path(shell, arguments, binary_name);
        return SUCCESS;
    }
    status = execute_binary(shell, binary_absolute_path, arguments);
    if (binary_absolute_path != NULL)
        free(binary_absolute_path);
    return status;
}

static
int get_number_argument(char **arguments)
{
    int nb_arguments = 0;

    if (arguments == NULL)
        return 0;
    while (arguments[nb_arguments] != NULL)
        nb_arguments += 1;
    return nb_arguments;
}

int execute_action(shell_t *shell, builtin_t *builtins, char **args)
{
    int nb_arguments = 0;
    char *binary_name = NULL;

    if (shell == NULL || args == NULL || args[0] == NULL)
        return FAILURE;
    shell->exit_status = 0;
    binary_name = args[0];
    nb_arguments = get_number_argument(args);
    for (int i = 0; i < NB_BUILTIN; i += 1) {
        if (my_strcmp(builtins->name[i], binary_name) == 0) {
            builtins->function[i](shell, args, nb_arguments);
            return shell->exit_status;
        }
    }
    if (execute_from_current_directory(shell, binary_name, args)
        != FAILURE || shell->exit_status != 0)
        return SUCCESS;
    return (shell->exit_status == 1) ?
        SUCCESS : execute_from_path(shell, binary_name, args);
}
