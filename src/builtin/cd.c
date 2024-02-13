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

int change_directory(shell_t *shell, char **arguments, int nb_arguments)
{
    char *home_directory = NULL;

    if (shell == NULL || shell->environment == NULL || nb_arguments > 2)
        return FAILURE;
    home_directory = get_home(shell->environment);
    if (home_directory == NULL)
        return FAILURE;
    if (nb_arguments == 1) {
        if (chdir(home_directory) != 0)
            return display_error("Unable to change the directory");
        return SUCCESS;
    }
    if (chdir(arguments[1]) != 0)
        return display_error("Unable to change the directory");
    return SUCCESS;
}
