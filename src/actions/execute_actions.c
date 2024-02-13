/*
** EPITECH PROJECT, 2024
** Actions
** File description:
** Execute the actions for the minishell project
*/

#include <stddef.h>
#include "dependencies/environment.h"
#include "builtin/builtin.h"
#include "my_macros.h"
#include "my.h"

int execute_action(environment_t *environment, builtin_t *builtin_array,
    char **arguments, int *alive)
{
    int nb_arguments = 0;

    if (arguments == NULL || arguments[0] == NULL)
        return FAILURE;
    while (arguments[nb_arguments] != NULL)
        nb_arguments += 1;
    for (int i = 0; i < 5; i += 1) {
        if (my_strcmp(builtin_array->name[i], arguments[0]) == 0)
            builtin_array->function[i](environment, arguments,
                nb_arguments, alive);
    }
    return SUCCESS;
}
