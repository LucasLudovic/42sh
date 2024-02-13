/*
** EPITECH PROJECT, 2024
** Exit
** File description:
** Exit the minishell
*/

#include "dependencies/environment.h"
#include "shell/my_shell.h"
#include "my_macros.h"

int exit_shell(shell_t *shell, UNUSED char **arguments, int nb_arguments)
{
    if (nb_arguments != 1)
        return FAILURE;
    shell->alive = FALSE;
    return SUCCESS;
}
