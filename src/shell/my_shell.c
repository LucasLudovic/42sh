/*
** EPITECH PROJECT, 2024
** Main
** File description:
** Shell for the minishell project
*/

#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <dependencies/environment.h>
#include "builtin/env.h"
#include "builtin/setenv.h"
#include "my.h"
#include "my_macros.h"

static
void print_prompt(void)
{
    write(1, "> ", 2);
}

int my_shell(char **environment)
{
    int shell_alive = TRUE;
    char **arguments = NULL;
    environment_t *shell_environment = NULL;

    shell_environment = get_environment(environment);
    while (shell_alive) {
        print_prompt();
        break;
    }
    env(shell_environment, NULL);
    my_putstr("\n\n\n");
    arguments = malloc(sizeof(char *) * 2);
    arguments[0] = "yo\n";
    arguments[1] = my_strdup("ZEBI=BONJOUR_JE_SUIS_UN_TEST");
    my_setenv(shell_environment, arguments, 2);
    env(shell_environment, NULL);
    return SUCCESS;
}
