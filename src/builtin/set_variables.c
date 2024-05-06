/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** set_variables.c
*/

#include "builtin/local_variable.h"
#include "my_macros.h"
#include "shell/my_shell.h"
#include <stdio.h>
#include <stdlib.h>

static
int retrieve_variable_value(variable_t *variable, char *argument,
    size_t const size)
{
    size_t len = 0;
    size_t i = 0;

    for (size_t k = (size + 1); argument[k] != '\0'; k += 1)
        len += 1;
    variable->value = malloc(sizeof(char) * (len + 1));
    if (variable->value == NULL)
        return FAILURE;
    for (size_t j = (size + 1); argument[j] != '\0'; j += 1) {
        variable->value[i] = argument[j];
        i += 1;
    }
    variable->value[i] = '\0';
    return SUCCESS;
}

static
int retrieve_variable_name(variable_t *variable, char *argument,
    size_t const size)
{
    variable->name = malloc(sizeof(char) * (size + 1));
    if (variable->name == NULL)
        return FAILURE;
    for (size_t k = 0; k < size && argument[k] != '\0'; k += 1) {
        variable->name[k] = argument[k];
    }
    variable->name[size] = '\0';
    return SUCCESS;
}

static
void check_equal(char *argument, int *equal, size_t *size)
{
    for (size_t j = 0; argument[j] != '\0'; j += 1) {
        if (argument[j] == '=') {
            *equal = TRUE;
            *size = j;
            break;
        }
    }
}

static
int check_format(shell_t *shell, char *argument)
{
    variable_t *head = shell->variable;
    variable_t *tmp = NULL;
    int equal = FALSE;
    size_t size = 0;

    check_equal(argument, &equal, &size);
    if (equal == TRUE && argument[size + 1] != '\0') {
        while (shell->variable->next != NULL)
            shell->variable = shell->variable->next;
        tmp = malloc(sizeof(variable_t));
        if (tmp == NULL)
            return FAILURE;
        shell->variable->next = tmp;
        if (retrieve_variable_name(tmp, argument, size) == FAILURE ||
            retrieve_variable_value(tmp, argument, size) == FAILURE)
            return FAILURE;
        tmp->next = NULL;
    }
    shell->variable = head;
    return SUCCESS;
}

int set(shell_t *shell, char **arguments, UNUSED int nb_arguments)
{
    if (shell == NULL || shell->variable == NULL || arguments == NULL ||
        arguments[0] == NULL)
        return FAILURE;
    for (size_t i = 1; arguments[i] != NULL; i += 1) {
        check_format(shell, arguments[i]);
    }
    return SUCCESS;
}
