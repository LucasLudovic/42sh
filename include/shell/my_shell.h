/*
** EPITECH PROJECT, 2024
** My Macros
** File description:
** Header file for minishell project
*/

#ifndef MY_SHELL_H_
    #define MY_SHELL_H_
    #include "builtin/local_variable.h"
    #include "dependencies/environment.h"
    #include "dependencies/history_struct.h"

typedef struct alias_s {
    char *initial_name;
    char *alias;
    struct alias_s *next;
} alias_t;

typedef struct shell_s {
    int alive;
    environment_t *environment;
    history_t *history;
    int exit_status;
    char *previous_path;
    alias_t *alias;
    variable_t *variable;
    int size_prompt;
} shell_t;

int my_shell(char **env);
int check_if_tty(void);
void print_prompt(shell_t *shell);
char **get_user_arguments(shell_t *shell, char **user_arguments);
int update_history(shell_t *shell, char const *cmd);
void destroy_history(history_t *history);

#endif
