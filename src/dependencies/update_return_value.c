/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** update_return_value.c
*/

#include "builtin/local_variable.h"
#include "shell/my_shell.h"
#include "my.h"
#include <stdio.h>
#include <string.h>
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

void update_return_value(shell_t *shell)
{
    char *return_value = malloc(sizeof(char) *
        (count_number(shell->exit_status) + 1));
    variable_t *head = shell->variable;

    if (shell == NULL)
        return;
    while (shell->variable->next != NULL) {
        if (strcmp(shell->variable->name, "?") == 0)
            break;
        shell->variable = shell->variable->next;
    }
    if (strcmp(shell->variable->name, "?") == 0) {
        if (shell->variable->value != NULL)
            free(shell->variable->value);
        sprintf(return_value, "%d", shell->exit_status);
        shell->variable->value = my_strdup(return_value);
        if (return_value != NULL)
            free(return_value);
    }
    shell->variable = head;
}
