/*
** EPITECH PROJECT, 2024
** Exit
** File description:
** Exit the minishell
*/

#include "dependencies/environment.h"
#include "my_macros.h"

int exit_shell(UNUSED environment_t **environment, UNUSED char **arguments,
    UNUSED int nb_arguments, int *alive)
{
    *alive = FALSE;
    return SUCCESS;
}
