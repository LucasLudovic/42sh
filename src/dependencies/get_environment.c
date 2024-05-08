/*
** EPITECH PROJECT, 2024
** Get environment
** File description:
** Get the environment for the minishell project
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "my_types.h"
#include "my.h"
#include "dependencies/environment.h"
#include "my_macros.h"

static
void destroy_single_node(environment_t **shell_environment)
{
    if ((*shell_environment)->next != NULL)
        destroy_single_node(&(*shell_environment)->next);
    if ((*shell_environment)->key != NULL) {
        free((*shell_environment)->key);
    }
    if ((*shell_environment)->value != NULL) {
        free((*shell_environment)->value);
    }
    (*shell_environment)->key = NULL;
    (*shell_environment)->value = NULL;
    free(*shell_environment);
    *shell_environment = NULL;
}

void destroy_environment_list(environment_t **shell_environment)
{
    if (shell_environment == NULL || *shell_environment == NULL)
        return;
    destroy_single_node(shell_environment);
}

static
environment_t *copy_single_variable(environment_t *environment, char *variable)
{
    environment->key = strtok(variable, "=");
    environment->value = strtok(NULL, "\n");
    if (my_strlen(environment->value) <= 0)
        environment->value = NULL;
    else
        environment->value = my_strdup(environment->value);
    return environment;
}

static
environment_t *copy_environment(environment_t *shell_environment, char **env)
{
    environment_t *head = NULL;
    char *env_copy = NULL;

    shell_environment = malloc(sizeof(environment_t));
    head = shell_environment;
    if (shell_environment == NULL)
        return NULL;
    for (uint64_t i = 0; env[i] != NULL; i += 1) {
        env_copy = my_strdup(env[i]);
        if (env_copy == NULL)
            return NULL;
        shell_environment = copy_single_variable(shell_environment, env_copy);
        if (env[i + 1] != NULL) {
            shell_environment->next = malloc(sizeof(environment_t));
            shell_environment = shell_environment->next;
        }
    }
    shell_environment->next = NULL;
    return head;
}

environment_t *get_environment(char **environment)
{
    environment_t *shell_environment = NULL;

    if (environment == NULL)
        return NULL;
    shell_environment = copy_environment(shell_environment, environment);
    return shell_environment;
}
