/*
** EPITECH PROJECT, 2024
** Alias
** File description:
** Give an alias to a command
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my_macros.h"
#include "shell/my_shell.h"

static
void print_history(history_t *history)
{
    if (!history)
        return;
    print_history(history->next);
    if (history->cmd && history->time)
        printf("%i\t%s\t%s\n", history->index, history->time, history->cmd);
}

int history(shell_t *shell, UNUSED char **arguments, UNUSED int nb_arguments)
{
    if (shell == NULL)
        return FAILURE;
    print_history(shell->history);
    return SUCCESS;
}
