/*
** EPITECH PROJECT, 2024
** Setenv
** File description:
** Add or modify the environment for the minishell project
*/

#include <stdlib.h>
#include <string.h>
#include "shell/my_shell.h"
#include "dependencies/environment.h"
#include "my_macros.h"
#include "my.h"

static
int check_sign_equal(const char *argument)
{
    if (argument == NULL)
        return FAILURE;
    for (int i = 0; argument[i] != '\0'; i += 1) {
        if (argument[i] == '=')
            return SUCCESS;
    }
    return FAILURE;
}

static
int check_node(environment_t *environment, char **key, char *value)
{
    if (my_strcmp(environment->key, *key) == 0) {
        if (environment->key == NULL)
            environment->next = NULL;
        if (environment->key != NULL)
            free(environment->key);
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
    *environment = malloc(sizeof(environment_t));
    if (*environment == NULL)
        return FAILURE;
    (*environment)->key = key;
    (*environment)->value = value;
    (*environment)->next = NULL;
    return SUCCESS;
}

static
int add_variable(environment_t *environment, char *argument)
{
    char *key = NULL;
    char *value = NULL;

    key = strtok(argument, "=");
    value = strtok(NULL, "\n");
    if (key == NULL || value == NULL || my_str_isupper(key) != TRUE) {
        if (key != NULL)
            free(key);
        if (value != NULL)
            free(value);
        return FAILURE;
    }
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
    if (shell->environment == NULL || arguments == NULL || nb_arguments != 2)
        return -1;
    if (check_sign_equal(arguments[1]) == FAILURE)
        return -1;
    if (add_variable(shell->environment, my_strdup(arguments[1])) == FAILURE)
        return -1;
    return SUCCESS;
}
