/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** unset_variables.c
*/

#include "builtin/local_variable.h"
#include "my_macros.h"
#include "shell/my_shell.h"
#include "my.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static
int destroy_node(variable_t *variable, variable_t *previous_variable,
    variable_t **head)
{
    if (variable == NULL)
        return FAILURE;
    if (previous_variable != NULL)
        previous_variable->next = variable->next;
    if (*head == variable)
        *head = variable->next;
    variable->next = NULL;
    if (variable->name != NULL)
        free(variable->name);
    if (variable->value != NULL)
        free(variable->value);
    free(variable);
    return SUCCESS;
}

static
int check_single_variable(shell_t *shell, variable_t *head,
    char **arguments, int index)
{
    variable_t *previous_variable = NULL;
    int number_unset = 0;

    while (shell->variable != NULL) {
        if (strcmp(shell->variable->name, arguments[index]) == 0) {
            destroy_node(shell->variable, previous_variable, &head);
            number_unset = 1;
            break;
        }
        previous_variable = shell->variable;
        shell->variable = shell->variable->next;
    }
    shell->variable = head;
    return number_unset;
}

int unset(shell_t *shell, char **arguments, int nb_arguments)
{
    variable_t *head = shell->variable;
    int number_unset = 0;

    if (shell->variable == NULL || arguments == NULL ||
        nb_arguments < 2) {
        shell->exit_status = 1;
        return display_error("unset: Too few arguments.\n");
    }
    for (int i = 0; arguments[i] != NULL; i += 1) {
        number_unset += check_single_variable(shell, head, arguments, i);
    }
    shell->variable = head;
    if (number_unset != nb_arguments - 1)
        return FAILURE;
    return SUCCESS;
}
