/*
** EPITECH PROJECT, 2024
** Setenv
** File description:
** Remove an environment variable for the minishell project
*/

#include <stdlib.h>
#include <stddef.h>
#include "shell/my_shell.h"
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

int my_unsetenv(shell_t *shell, char **arguments, int nb_arguments)
{
    environment_t *previous_variable = NULL;
    environment_t *head = shell->environment;

    if (shell->environment == NULL || arguments == NULL || nb_arguments != 2)
        return FAILURE;
    while (shell->environment != NULL) {
        if (my_strcmp(shell->environment->key, arguments[1]) == 0) {
            destroy_node(shell->environment, previous_variable, &head);
            shell->environment = head;
            return SUCCESS;
        }
        previous_variable = shell->environment;
        shell->environment = shell->environment->next;
    }
    shell->environment = head;
    return FAILURE;
}
