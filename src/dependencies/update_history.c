/*
** EPITECH PROJECT, 2024
** Update history
** File description:
** Update history for the minishell project
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "dependencies/history_struct.h"
#include "my.h"
#include "shell/my_shell.h"

void destroy_history(history_t *history)
{
    if (history != NULL && history->cmd != NULL) {
        destroy_history(history->next);
        free(history->cmd);
        free(history);
    }
}

int update_history(shell_t *shell, char const *cmd)
{
    history_t *tmp = NULL;

    if (shell == NULL || cmd == NULL)
        return FAILURE;
    tmp = malloc(sizeof(history_t));
        if (tmp == NULL)
            return FAILURE;
    tmp->cmd = strdup(cmd);
        if (tmp->cmd == NULL)
            return FAILURE;
    tmp->next = shell->history;
    shell->history = tmp;
    return SUCCESS;
}
