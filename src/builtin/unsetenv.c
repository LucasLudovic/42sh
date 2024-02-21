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

static
int check_single_variable(shell_t *shell, environment_t *head,
    char **arguments, int index)
{
    environment_t *previous_variable = NULL;
    int number_unset = 0;

    while (shell->environment != NULL) {
        if (my_strcmp(shell->environment->key, arguments[index]) == 0) {
            destroy_node(shell->environment, previous_variable, &head);
            number_unset = 1;
            break;
        }
        previous_variable = shell->environment;
        shell->environment = shell->environment->next;
    }
    shell->environment = head;
    return number_unset;
}

int my_unsetenv(shell_t *shell, char **arguments, int nb_arguments)
{
    environment_t *head = shell->environment;
    int number_unset = 0;

    if (shell->environment == NULL || arguments == NULL ||
        nb_arguments < 2) {
        shell->exit_status = 1;
        return display_error("unsetenv: Too few arguments.\n");
    }
    for (int i = 0; arguments[i] != NULL; i += 1) {
        number_unset += check_single_variable(shell, head, arguments, i);
    }
    shell->environment = head;
    if (number_unset != nb_arguments - 1)
        return FAILURE;
    return SUCCESS;
}
