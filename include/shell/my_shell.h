/*
** EPITECH PROJECT, 2024
** My Macros
** File description:
** Header file for minishell project
*/

#ifndef MY_SHELL_H_
    #define MY_SHELL_H_
    #include "dependencies/environment.h"

typedef struct alias_s {
    char *initial_name;
    char *alias;
    struct alias_s *next;
} alias_t;

typedef struct shell_s {
    int alive;
    environment_t *environment;
    int exit_status;
    char *previous_path;
    alias_t *alias;
} shell_t;

int my_shell(char **env);
void print_prompt(shell_t *shell);

#endif
