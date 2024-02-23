/*
** EPITECH PROJECT, 2024
** Setenv
** File description:
** Add or modify the environment for the minishell project
*/

#include <stdlib.h>
#include <string.h>
#include <builtin/env.h>
#include "shell/my_shell.h"
#include "dependencies/environment.h"
#include "my_macros.h"
#include "my.h"

static
int check_node(environment_t *environment, char **key, char *value)
{
    if (my_strcmp(environment->key, *key) == 0) {
        if (environment->key == NULL)
            environment->next = NULL;
        if (environment->key != NULL)
            free(environment->key);
        if (environment->value != NULL)
            free(environment->value);
        environment->key = *key;
        environment->value = value;
        return SUCCESS;
    }
    return FAILURE;
}

static
int add_new_variable(environment_t **environment, char *key, char *value)
{
    if (environment == NULL)
        return FAILURE;
    if (environment != NULL)
        *environment = malloc(sizeof(environment_t));
    (*environment)->key = NULL;
    (*environment)->value = NULL;
    if (*environment == NULL)
        return FAILURE;
    (*environment)->key = key;
    if ((*environment)->value != NULL)
        free((*environment)->value);
    (*environment)->value = value;
    (*environment)->next = NULL;
    return SUCCESS;
}

static
int destroy_set_variables(char *key, char **value)
{
    if (key == NULL) {
        if (*value != NULL)
            free(*value);
        *value = NULL;
        return FAILURE;
    }
    return SUCCESS;
}

static
int add_variable_and_value(environment_t *environment, char **arguments)
{
    char *key = NULL;
    char *value = NULL;

    key = my_strdup(arguments[1]);
    if (arguments[2] != NULL)
        value = my_strdup(arguments[2]);
    if (destroy_set_variables(key, &value) == FAILURE)
        return FAILURE;
    while (environment->next != NULL) {
        if (check_node(environment, &key, value) == SUCCESS)
            return SUCCESS;
        environment = environment->next;
    }
    if (check_node(environment, &key, value) == SUCCESS)
        return SUCCESS;
    return add_new_variable(&environment->next, key, value);
}

int my_setenv(shell_t *shell, char **arguments, int nb_arguments)
{
    if (shell->environment == NULL || arguments == NULL || nb_arguments < 2 ||
        nb_arguments > 3)
        if (nb_arguments == 1) {
            env(shell, arguments, 1);
            return -1;
        }
    if (!my_str_is_alpha_num(arguments[1])) {
        shell->exit_status = 1;
        display_error("setenv: Variable name must contain ");
        display_error("alphanumeric characters.\n");
        return -1;
    }
    if (add_variable_and_value(shell->environment, arguments) == FAILURE)
        return -1;
    return SUCCESS;
}
