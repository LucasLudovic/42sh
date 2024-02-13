/*
** EPITECH PROJECT, 2024
** Environment
** File description:
** Header to get the user environment for the minishell1 project
*/

#ifndef ENVIRONMENT_H_
    #define ENVIRONMENT_H_

typedef struct environment_s {
    char *key;
    char *value;
    struct environment_s *next;
} environment_t;

environment_t *get_environment(char **environment);
void destroy_environment_list(environment_t *shell_environment);

#endif
