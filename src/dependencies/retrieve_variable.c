/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** retrieve_variable.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "builtin/local_variable.h"
#include "dependencies/environment.h"
#include "my.h"
#include "my_macros.h"
#include "shell/my_shell.h"

static char *search_variable_env(shell_t *shell, char *argument)
{
    environment_t *head = NULL;
    char *new_value = NULL;

    if (shell->environment == NULL)
        return NULL;
    head = shell->environment;
    while (shell->environment->next != NULL) {
        if (strcmp(shell->environment->key, argument) == 0)
            break;
        shell->environment = shell->environment->next;
    }
    if (strcmp(shell->environment->key, argument) == 0) {
        new_value = my_strdup(shell->environment->value);
        shell->environment = head;
        return new_value;
    }
    shell->environment = head;
    return NULL;
}

static char *search_variable_local(shell_t *shell, char *argument)
{
    variable_t *head = NULL;
    char *new_value = NULL;

    if (shell->variable == NULL)
        return NULL;
    head = shell->variable;
    while (shell->variable->next != NULL) {
        if (strcmp(shell->variable->name, argument) == 0)
            break;
        shell->variable = shell->variable->next;
    }
    if (strcmp(shell->variable->name, argument) == 0) {
        new_value = my_strdup(shell->variable->value);
        shell->variable = head;
        return new_value;
    }
    shell->variable = head;
    return NULL;
}

static int check_dollar(shell_t *shell, char **argument)
{
    char *new_value = NULL;

    if (strncmp(*argument, "$", 1) == 0) {
        new_value = search_variable_env(shell, *argument + 1);
    }
    if (new_value == NULL) {
        if (strncmp(*argument, "$", 1) == 0)
            new_value = search_variable_local(shell, *argument + 1);
    }
    if (*argument != NULL && new_value != NULL)
        free(*argument);
    if (new_value == NULL)
        return SUCCESS;
    *argument = strdup(new_value);
    free(new_value);
    return SUCCESS;
}

void retrieve_variable(shell_t *shell, char **arguments)
{
    if (arguments == NULL || arguments[0] == NULL)
        return;
    for (size_t i = 0; arguments[i] != NULL; i++) {
        check_dollar(shell, &arguments[i]);
    }
}
