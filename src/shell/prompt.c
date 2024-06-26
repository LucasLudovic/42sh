/*
** EPITECH PROJECT, 2024
** Prompt
** File description:
** Display the prompt for the minishell project
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include "dependencies/environment.h"
#include "my.h"
#include "shell/my_shell.h"

static
void get_home(shell_t *shell, char **home_directory)
{
    environment_t *head = shell->environment;

    while (shell->environment != NULL) {
        if (my_strcmp(shell->environment->key, "HOME") == 0) {
            *home_directory = shell->environment->value;
            break;
        }
        shell->environment = shell->environment->next;
    }
    shell->environment = head;
}

static
void remove_home_from_directory(char *home_directory, char **current_directory,
    int *movement)
{
    if (my_strncmp(home_directory, *current_directory,
        my_strlen(home_directory)) == 0)
        *movement = my_strlen(home_directory) + 1;
    if (my_strlen(*current_directory) - *movement >= 1)
        *current_directory += *movement;
    else
        *movement = 0;
}

static
void display_simple_prompt(shell_t *shell)
{
    if (shell == NULL)
        return;
    if (shell->exit_status == 0)
        display_string_colored("~> ", "green");
    else
        display_string_colored("x> ", "red");
}

static
void display_branch(void)
{
    FILE *fp = NULL;
    char name[128];
    char *branch = NULL;
    int repo = system("git rev-parse --is-inside-work-tree > /dev/null 2>&1");

    if (repo == SUCCESS) {
        fp = popen("git rev-parse --abbrev-ref HEAD", "r");
        fgets(name, 128, fp);
        branch = my_strdup(name);
        branch[my_strlen(name) - 1] = '\0';
        display_string_colored("(", "blue");
        display_string_colored(branch, "purple");
        display_string_colored(") ", "blue");
        pclose(fp);
        free(branch);
    }
}

static
void display_directory(char *current_directory, char *home_directory)
{
    if (my_strcmp(current_directory, home_directory) == 0)
        display_string_colored("~", "cyan");
    else
        display_string_colored(current_directory, "cyan");
    my_putchar(' ');
    display_branch();
}

static
void destroy_current_directory(shell_t *shell, environment_t *head,
    char *current_directory, int movement)
{
    current_directory -= movement;
    free(current_directory);
    shell->environment = head;
}

void print_prompt(shell_t *shell)
{
    char *current_directory = NULL;
    char *home_directory = NULL;
    environment_t *head = NULL;
    int movement = 0;

    if (shell == NULL)
        return;
    head = shell->environment;
    display_simple_prompt(shell);
    current_directory = getcwd(current_directory, 0);
    if (current_directory == NULL)
        return;
    get_home(shell, &home_directory);
    if (home_directory == NULL) {
        free(current_directory);
        return;
    }
    remove_home_from_directory(home_directory, &current_directory, &movement);
    display_directory(current_directory, home_directory);
    destroy_current_directory(shell, head, current_directory, movement);
}
