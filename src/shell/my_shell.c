/*
** EPITECH PROJECT, 2024
** Main
** File description:
** Shell for the minishell project
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <dependencies/environment.h>
#include "builtin/builtin.h"
#include "builtin/env.h"
#include "builtin/setenv.h"
#include "builtin/exit.h"
#include "my.h"
#include "my_macros.h"

static
void destroy_end(environment_t *shell_environment, builtin_t *builtin_array)
{
    destroy_environment_list(shell_environment);
    if (builtin_array == NULL)
        return;
    for (int i = 0; i < 5; i += 1) {
        if (builtin_array->name[i] != NULL)
            free(builtin_array->name[i]);
    }
}

static
int initialize_function_pointer_array(builtin_t *builtin_array)
{
    builtin_array->name[0] = my_strdup("env");
    builtin_array->function[0] = &env;
    builtin_array->name[1] = my_strdup("setenv");
    builtin_array->function[1] = &my_setenv;
    builtin_array->name[2] = my_strdup("unsetenv");
    builtin_array->function[2] = NULL;
    builtin_array->name[3] = my_strdup("exit");
    builtin_array->function[3] = &exit_shell;
    builtin_array->name[4] = my_strdup("cd");
    builtin_array->function[4] = NULL;
    if (builtin_array->name[0] == NULL || builtin_array->name[1] == NULL ||
        builtin_array->name[2] == NULL || builtin_array->name[3] == NULL ||
        builtin_array->name[4] == NULL)
        return FAILURE;
    return SUCCESS;
}

static
void print_prompt(void)
{
    write(1, "> ", 2);
}

static
char **get_user_arguments(char **user_arguments)
{
    char *user_input = NULL;
    size_t size = 0;

    getline(&user_input, &size, stdin);
    if (user_input == NULL)
        return NULL;
    user_arguments = my_str_to_word_array(user_input);
    free(user_input);
    return user_arguments;
}

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

int my_shell(char **environment)
{
    int shell_alive = TRUE;
    builtin_t builtin_array = { 0 };
    char **user_arguments = NULL;
    environment_t *shell_environment = NULL;

    if (initialize_function_pointer_array(&builtin_array) == FAILURE)
        return FAILURE;
    shell_environment = get_environment(environment);
    while (shell_alive) {
        print_prompt();
        user_arguments = get_user_arguments(user_arguments);
        if (user_arguments == NULL)
            return FAILURE;
        if (execute_action(shell_environment, &builtin_array,
            user_arguments, &shell_alive) == FAILURE)
            return FAILURE;
    }
    if (shell_environment != NULL)
        destroy_end(shell_environment, &builtin_array);
    return SUCCESS;
}
