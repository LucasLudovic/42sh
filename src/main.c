/*
** EPITECH PROJECT, 2024
** Main
** File description:
** Main for the minishell project
*/

#include "my_macros.h"
#include "shell/my_shell.h"
#include "my.h"
#include <stddef.h>

int main(UNUSED const int argc, UNUSED char *const *argv, char **env)
{
    if (env == NULL || env[0] == NULL)
        return display_error("Unable to locate the environment\n");
    if (argc != 1)
        return display_error("There's no need to provide any argument\n");
    return my_shell(env);
}
