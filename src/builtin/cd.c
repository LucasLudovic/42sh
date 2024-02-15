/*
** EPITECH PROJECT, 2024
** Cd
** File description:
** Change the directory for the minishell project
*/

#include <unistd.h>
#include <stddef.h>
#include "shell/my_shell.h"
#include "my_macros.h"
#include "my.h"
#include <stdlib.h>

static
char *get_home(environment_t *environment)
{
    while (environment != NULL) {
        if (my_strcmp(environment->key, "HOME") == 0)
            return environment->value;
        environment = environment->next;
    }
    return NULL;
}

static
void update_previous_path(shell_t *shell, char *previous_path)
{
    if (previous_path == NULL)
        previous_path = getcwd(previous_path, 0);
    if (shell->previous_path != NULL)
        free(shell->previous_path);
    shell->previous_path = previous_path;
}

static
int return_previous_directory(shell_t *shell, char **previous_path)
{
    if (shell->previous_path == NULL)
        return FAILURE;
    *previous_path = getcwd(*previous_path, 0);
    if (chdir(shell->previous_path) != 0) {
        shell->exit_status = FAILURE;
        return FAILURE;
    }
    update_previous_path(shell, *previous_path);
    return SUCCESS;
}

static
int return_to_home(char *home_directory)
{
    if (chdir(home_directory) != 0)
        return display_error("Unable to change the directory\n");
    return SUCCESS;
}

int change_directory(shell_t *shell, char **arguments, int nb_arguments)
{
    char *home_directory = NULL;
    char *previous_path = NULL;

    if (shell == NULL || shell->environment == NULL || nb_arguments > 2)
        return FAILURE;
    home_directory = get_home(shell->environment);
    if (home_directory == NULL && (nb_arguments == 1 ||
            (nb_arguments == 2 && my_strcmp(arguments[1], "~") == 0)))
        return FAILURE;
    if (nb_arguments == 2 && my_strcmp(arguments[1], "-") == 0) {
        return return_previous_directory(shell, &previous_path);
    }
    update_previous_path(shell, previous_path);
    if (nb_arguments == 1 || my_strcmp(arguments[1], "~") == 0)
        return return_to_home(home_directory);
    if (chdir(arguments[1]) != 0)
        return display_error("Unable to change the directory\n");
    return SUCCESS;
}
