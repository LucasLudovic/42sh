/*
** EPITECH PROJECT, 2024
** Actions
** File description:
** Execute the actions for the minishell project
*/

#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include "my_alloc.h"
#include "dependencies/which.h"
#include "dependencies/environment.h"
#include "builtin/builtin.h"
#include "my_macros.h"
#include "my.h"

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
        return display_error("Can't access the file\n");
    }
    current_pid = fork();
    if (current_pid == 0) {
        execve(path, arguments, environment_array);
        exit(FAILURE);
    }
    waitpid(-1, &wait_status, 0);
    destroy_environment_array(environment_array);
    shell->exit_status = wait_status;
    return SUCCESS;
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
int execute_from_current_directory(shell_t *shell, char **arguments)
{
    if (arguments == NULL || arguments[0] == NULL ||
        my_strncmp(arguments[0], "./", 2) != 0)
        return FAILURE;
    if (my_strlen(arguments[0]) < 3)
        return FAILURE;
    if (check_current_directory(arguments[0] + 2) == FALSE)
        return FAILURE;
    return execute_binary(shell, arguments[0] + 2, arguments);
}

static
int execute_from_path(shell_t *shell, char **arguments)
{
    char *binary_absolute_path = NULL;
    int status = FAILURE;

    if (shell == NULL || arguments == NULL)
        return FAILURE;
    binary_absolute_path = get_function_absolute_path(shell->environment,
        arguments);
    if (binary_absolute_path == NULL)
        return FAILURE;
    status = execute_binary(shell, binary_absolute_path, arguments);
    if (binary_absolute_path != NULL)
        free(binary_absolute_path);
    return status;
}

int execute_action(shell_t *shell, builtin_t *builtin_array, char **arguments)
{
    int nb_arguments = 0;

    if (arguments == NULL || arguments[0] == NULL)
        return FAILURE;
    while (arguments[nb_arguments] != NULL)
        nb_arguments += 1;
    for (int i = 0; i < 5; i += 1) {
        if (my_strcmp(builtin_array->name[i], arguments[0]) == 0)
            return builtin_array->function[i](shell, arguments,
                nb_arguments);
    }
    if (execute_from_current_directory(shell, arguments) == SUCCESS)
        return SUCCESS;
    return execute_from_path(shell, arguments);
}
