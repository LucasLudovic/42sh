/*
** EPITECH PROJECT, 2024
** Update history
** File description:
** Update history for the minishell project
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "dependencies/history_struct.h"
#include "my.h"
#include "shell/my_shell.h"

void destroy_history(history_t *history)
{
    if (history != NULL) {
        destroy_history(history->next);
        if (history->cmd)
            free(history->cmd);
        if (history->time)
            free(history->time);
        free(history);
    }
}

static
char *get_time(void)
{
    char *time_str = malloc(sizeof(char) * 6);
    time_t now;
    struct tm *local = NULL;

    if (!time_str)
        return NULL;
    time(&now);
    local = localtime(&now);
    sprintf(time_str, "%02d:%02d", local->tm_hour, local->tm_min);
    return time_str;
}

int update_history(shell_t *shell, char const *cmd)
{
    history_t *tmp = NULL;

    if (shell == NULL || cmd == NULL)
        return FAILURE;
    tmp = malloc(sizeof(history_t));
    if (!tmp)
        return FAILURE;
    tmp->cmd = strdup(cmd);
    if (!tmp->cmd)
        return FAILURE;
    tmp->time = get_time();
    if (!tmp->time)
        return FAILURE;
    tmp->index = (shell->history) ? shell->history->index + 1 : 1;
    tmp->next = shell->history;
    shell->history = tmp;
    return SUCCESS;
}
