/*
** EPITECH PROJECT, 2024
** Main
** File description:
** Shell for the minishell project
*/

#include <stddef.h>
#include <unistd.h>
#include "my_macros.h"

static
void print_prompt(void)
{
    write(1, "> ", 2);
}

int my_shell(int number_of_arguments, char **arguments, char **env)
{
    int shell_alive = TRUE;
    char *command_user = NULL;
    char **shell_env;

    shell_environment = get_environment();
    while (shell_alive) {
        print_prompt();
        get_usr_command();
        exec_usr_command();
    }
    return SUCCESS;
}
