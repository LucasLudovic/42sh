/*
** EPITECH PROJECT, 2024
** Env
** File description:
** Print the environment for the minishell project
*/

#include <stddef.h>
#include "dependencies/environment.h"
#include "my.h"
#include "my_macros.h"

int env(environment_t **environment, UNUSED char **arguments,
    int nb_arguments, UNUSED int *alive)
{
    environment_t *head = NULL;

    if (environment == NULL)
        return FAILURE;
    head = *environment;
    if (nb_arguments != 1) {
        display_error("Wrong number of arguments\n");
        return FAILURE;
    }
    while (*environment != NULL) {
        if ((*environment)->key != NULL && (*environment)->value != NULL) {
            my_putstr((*environment)->key);
            my_putchar('=');
            my_putstr((*environment)->value);
            my_putchar('\n');
        }
        *environment = (*environment)->next;
    }
    *environment = head;
    return SUCCESS;
}
