/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** initialize_builtins.c
*/

#include <builtin/builtin.h>
#include "builtin/cd.h"
#include "builtin/env.h"
#include "builtin/exit.h"
#include "builtin/alias.h"
#include "builtin/setenv.h"
#include "builtin/history.h"
#include "builtin/unsetenv.h"
#include "builtin/set_variables.h"
#include "my.h"
#include <stdio.h>

static
int check_initialization(builtin_t *builtin_array)
{
    if (builtin_array->name[0] == NULL || builtin_array->name[1] == NULL ||
        builtin_array->name[2] == NULL || builtin_array->name[3] == NULL ||
        builtin_array->name[4] == NULL || builtin_array->name[5] == NULL ||
        builtin_array->name[6] == NULL || builtin_array->name[7] == NULL)
        return FAILURE;
    return SUCCESS;
}

int initialize_function_pointer_array(builtin_t *builtin_array)
{
    builtin_array->name[0] = my_strdup("env");
    builtin_array->function[0] = &env;
    builtin_array->name[1] = my_strdup("setenv");
    builtin_array->function[1] = &my_setenv;
    builtin_array->name[2] = my_strdup("unsetenv");
    builtin_array->function[2] = &my_unsetenv;
    builtin_array->name[3] = my_strdup("exit");
    builtin_array->function[3] = &exit_shell;
    builtin_array->name[4] = my_strdup("cd");
    builtin_array->function[4] = &change_directory;
    builtin_array->name[5] = my_strdup("alias");
    builtin_array->function[5] = &replace_alias;
    builtin_array->name[6] = my_strdup("history");
    builtin_array->function[6] = &history;
    builtin_array->name[7] = my_strdup("set");
    builtin_array->function[7] = &set;
    if (check_initialization(builtin_array) == FAILURE)
        return FAILURE;
    return SUCCESS;
}
