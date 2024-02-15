/*
** EPITECH PROJECT, 2024
** Alias
** File description:
** Give an alias to a command
*/

#include <stddef.h>
#include "my.h"
#include "my_macros.h"
#include "shell/my_shell.h"

char *check_alias(alias_t *alias, char *name)
{
    if (alias == NULL || name == NULL)
        return NULL;
    while (alias != NULL) {
        if (alias->alias == NULL || alias->initial_name == NULL)
            return NULL;
        if (my_strcmp(alias->alias, name) == 0)
            return alias->initial_name;
        alias = alias->next;
    }
    return name;
}

int change_name(UNUSED char **arguments)
{
    return SUCCESS;
}
