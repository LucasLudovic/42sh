/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Which builtin for 42sh
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "dependencies/which.h"
#include "my_macros.h"
#include "shell/my_shell.h"

int which(shell_t *shell, char **arguments, UNUSED int nb_arguments)
{
    char *path = NULL;

    if (shell == NULL || arguments == NULL || arguments[1] == NULL) {
        shell->exit_status = 1;
        return FAILURE;
    }
    for (size_t i = 1; arguments[i] != NULL; i++) {
        path = get_function_absolute_path(shell->environment, &arguments[i]);
        if (path != NULL) {
            printf("%s\n", path);
            free(path);
        } else {
            printf("%s: Command not found.\n", arguments[i]);
            shell->exit_status = 1;
        }
    }
    return SUCCESS;
}
