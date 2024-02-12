/*
** EPITECH PROJECT, 2024
** Get environment
** File description:
** Get the environment for the minishell project
*/

#include <stdlib.h>
#include <unistd.h>
#include "dependencies/environment.h"
#include "my_macros.h"

static
void destroy_single_node(environment_t *shell_environment)
{
    if (shell_environment->next != NULL) {
        destroy_single_node(shell_environment->next);
    }
    if (shell_environment->key != NULL)
        free(shell_environment->key);
    if (shell_environment->value != NULL)
        free(shell_environment->value);
    free(shell_environment);
}

static
void destroy_environment_list(environment_t *shell_environment)
{
    if (shell_environment == NULL)
        return;
    destroy_single_node(shell_environment);
}

static
environment_t *copy_environment(environment_t *shell_environment, char **env)
{
    char *environment_array = NULL;

    shell_environment = malloc(sizeof(environment_t));
    return shell_environment;
}

environment_t *get_environment(char **environment)
{
    environment_t *shell_environment = malloc(sizeof(environment_t));

    if (shell_environment == NULL || environment == NULL)
        return NULL;
    copy_environment(shell_environment, environment);
    return shell_environment;
}
