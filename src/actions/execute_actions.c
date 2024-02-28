/*
** EPITECH PROJECT, 2024
** Actions
** File description:
** Execute the actions for the minishell project
*/

#include <iso646.h>
#include <signal.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include "my_alloc.h"
#include "dependencies/which.h"
#include "dependencies/environment.h"
#include "builtin/builtin.h"
#include "builtin/alias.h"
#include "my_macros.h"
#include "my.h"

static
int display_error_message(shell_t *shell, char *binary_name, int status)
{
    if (shell != NULL)
        shell->exit_status = (status >= 256) ? status / 256 : status;
    if (status == 136)
        display_error("Floating exception (core dumped)\n");
    if (status == 139)
        display_error("Segmentation fault (core dumped)\n");
    if (shell->exit_status == 1) {
        if (binary_name != NULL)
            display_error(binary_name);
        return display_error(": Permission denied.\n");
    }
    return SUCCESS;
}

static
int execute_binary(shell_t *shell, char *path, char **arguments)
{
    pid_t current_pid = 0;
    char **environment_array = NULL;
    int wait_status = 0;

    if (path == NULL || arguments == NULL || arguments[0] == NULL)
        return FAILURE;
    environment_array = convert_environment_to_array(shell->environment);
    if (access(path, X_OK) != 0 || environment_array == NULL) {
        destroy_environment_array(environment_array);
        return display_error_message(shell, arguments[0], 1);
    }
    current_pid = fork();
    if (current_pid == 0) {
        execve(path, arguments, environment_array);
        exit(FAILURE);
    } else
    waitpid(-1, &wait_status, 0);
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
        !check_as_absolute(binary_name))
        return FAILURE;
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
int execute_from_path(shell_t *shell, UNUSED char *binary_name,
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

int execute_action(shell_t *shell, builtin_t *builtin_array, char **arguments)
{
    int nb_arguments = 0;
    char *binary_name = NULL;

    shell->exit_status = 0;
    if (shell == NULL || arguments == NULL || arguments[0] == NULL)
        return FAILURE;
    binary_name = arguments[0];
    while (arguments[nb_arguments] != NULL)
        nb_arguments += 1;
    for (int i = 0; i < 5; i += 1) {
        if (my_strcmp(builtin_array->name[i], binary_name) == 0) {
            builtin_array->function[i](shell, arguments,
                nb_arguments);
            return shell->exit_status;
        }
    }
    if (execute_from_current_directory(shell, binary_name, arguments) == 0)
        return SUCCESS;
    return (shell->exit_status == 1) ?
        SUCCESS : execute_from_path(shell, binary_name, arguments);
}
