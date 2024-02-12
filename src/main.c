/*
** EPITECH PROJECT, 2024
** Main
** File description:
** Main for the minishell project
*/

#include "my_macros.h"
#include "shell/my_shell.h"

int main(UNUSED const int argc, UNUSED const char *const *argv, char **env)
{
    return my_shell(env);
}
