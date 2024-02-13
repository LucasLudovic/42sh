/*
** EPITECH PROJECT, 2024
** Env
** File description:
** Print the environment for the minishell project
*/

#include <stddef.h>
#include "dependencies/environment.h"
#include "shell/my_shell.h"
#include "my.h"
#include "my_macros.h"

static
void display_single_node(shell_t *shell)
{
    if (shell->environment->key != NULL &&
        shell->environment->value != NULL) {
        my_putstr(shell->environment->key);
        my_putchar('=');
        my_putstr(shell->environment->value);
        my_putchar('\n');
    }
}

int env(shell_t *shell, UNUSED char **arguments, int nb_arguments)
{
    environment_t *head = NULL;

    if (shell->environment == NULL)
        return FAILURE;
    head = shell->environment;
    if (nb_arguments != 1) {
        display_error("Wrong number of arguments\n");
        return FAILURE;
    }
    while (shell->environment != NULL) {
        display_single_node(shell);
        shell->environment = shell->environment->next;
    }
    shell->environment = head;
    return SUCCESS;
}
