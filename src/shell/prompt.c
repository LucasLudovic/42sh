/*
** EPITECH PROJECT, 2024
** Prompt
** File description:
** Display the prompt for the minishell project
*/

#include <stdlib.h>
#include "my.h"
#include "unistd.h"
#include "shell/my_shell.h"

void print_prompt(shell_t *shell)
{
    char *current_directory = NULL;
    char *home_directory = NULL;
    environment_t *head = NULL;
    int movement = 0;

    if (shell == NULL)
        return;
    head = shell->environment;
    if (shell->exit_status == 0)
        display_string_colored("~> ", "green");
    else
        display_string_colored("x> ", "red");
    current_directory = getcwd(current_directory, 0);
    if (current_directory == NULL)
        return;
    while (shell->environment != NULL) {
        if (shell->environment == NULL)
            return;
        if (my_strcmp(shell->environment->key, "HOME") == 0)
            home_directory = shell->environment->value;
        shell->environment = shell->environment->next;
    }
    if (home_directory == NULL)
        return;
    if (my_strncmp(home_directory, current_directory, my_strlen(home_directory)) == 0) {
        movement = my_strlen(home_directory) + 1;
    }
    if (my_strlen(current_directory) - movement >= 1)
        current_directory += movement;
    else
        movement = 0;
    if (my_strcmp(current_directory, home_directory) == 0)
        display_string_colored("~", "blue");
    else
        display_string_colored(current_directory, "blue");
    my_putchar(' ');
    current_directory -= movement;
    free(current_directory);
    shell->environment = head;
}