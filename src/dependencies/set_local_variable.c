/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** set_local_variable
*/

#include "builtin/local_variable.h"
#include "my.h"
#include "shell/my_shell.h"
#include <stdio.h>
#include <stdlib.h>

static int count_number(int nb)
{
    int count = 1;

    while (nb > 0) {
        count += 1;
        nb /= 10;
    }
    return count;
}

int set_local_variable(shell_t *my_shell)
{
    char *return_value = malloc(sizeof(char) *
        (count_number(my_shell->exit_status) + 1));

    if (my_shell == NULL)
        return FAILURE;
    if (my_shell == NULL)
        return FAILURE;
    return_value[count_number(my_shell->exit_status)] = '\0';
    my_shell->variable = malloc(sizeof(variable_t));
    if (my_shell->variable == NULL)
        return FAILURE;
    my_shell->variable->name = my_strdup("?");
    sprintf(return_value, "%d", my_shell->exit_status);
    my_shell->variable->value = return_value;
    my_shell->variable->next = malloc(sizeof(variable_t));
    my_shell->variable->next->name = my_strdup("HOME");
    my_shell->variable->next->value = my_strdup("~");
    my_shell->variable->next->next = NULL;
    return SUCCESS;
}

void free_local_variable(variable_t *variable)
{
    variable_t *tmp = NULL;

    if (variable == NULL)
        return;
    while (variable != NULL) {
        tmp = variable->next;
        free(variable->name);
        free(variable->value);
        free(variable);
        variable = tmp;
    }
}
