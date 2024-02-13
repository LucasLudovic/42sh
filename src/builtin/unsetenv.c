/*
** EPITECH PROJECT, 2024
** Setenv
** File description:
** Remove an environment variable for the minishell project
*/

#include <stdlib.h>
#include <stddef.h>
#include "dependencies/environment.h"
#include "my_macros.h"
#include "my.h"

static
int destroy_node(environment_t *environment, environment_t *previous_variable,
    environment_t **head)
{
    if (environment == NULL)
        return FAILURE;
    if (previous_variable != NULL)
        previous_variable->next = environment->next;
    if (*head == environment)
        *head = environment->next;
    environment->next = NULL;
    destroy_environment_list(&environment);
    return SUCCESS;
}

int my_unsetenv(environment_t **environment, char **arguments,
    int nb_arguments, UNUSED int *alive)
{
    environment_t *previous_variable = NULL;
    environment_t *head = *environment;

    if ((*environment) == NULL || arguments == NULL || nb_arguments != 2)
        return FAILURE;
    while (*environment != NULL) {
        if (my_strcmp((*environment)->key, arguments[1]) == 0) {
            destroy_node(*environment, previous_variable, &head);
            *environment = head;
            return SUCCESS;
        }
        previous_variable = *environment;
        *environment = (*environment)->next;
    }
    *environment = head;
    return FAILURE;
}
