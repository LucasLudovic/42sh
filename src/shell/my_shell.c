/*
** EPITECH PROJECT, 2024
** Main
** File description:
** Shell for the minishell project
*/

#include <stddef.h>
#include <unistd.h>
#include "my.h"
#include "my_macros.h"

static
void print_prompt(void)
{
    write(1, "> ", 2);
}

int exec_user_command(char **shell_environment)
{
    char *user_command = NULL;

    get_user_command();
    if (user_command != shell_command)
        check_command_output();
    return SUCCESS;
}

int my_shell(int number_of_arguments, char **arguments, char **environment)
{
    int shell_alive = TRUE;
    char **shell_environment;

    shell_environment = get_environment(environment);
    while (shell_alive) {
        print_prompt();
        shell_alive = exec_user_command(shell_environment);
    }
    return SUCCESS;
}
