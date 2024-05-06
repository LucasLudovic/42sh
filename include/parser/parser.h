/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Parser
*/

#ifndef PARSER_H_
    #define PARSER_H_
    #include "shell/my_shell.h"
    #include "builtin/builtin.h"
    #define NO_COMPARATOR 0
    #define AND 1
    #define OR 2


typedef struct pipes_split_s {
    char **arguments;
    char *path;
    struct pipes_split_s *next;
} pipes_splits_t;

typedef struct comparison_s {
    char *argument;
    char previous_comparator;
    struct comparison_s *next;
} comparison_t;

char **parse_semicolon(char *str);
char **parse_double_left_redirection(char *str);
char **parse_double_right_redirection(char *str, int *fd);
char **parse_single_left_redirection(char *str, int *fd);
char **parse_single_right_redirection(char *str, int *fd);
pipes_splits_t *parse_pipes(char **arguments);
int check_ambiguity(char **str);
int execute_pipe(shell_t *shell, builtin_t *builtin_array,
    pipes_splits_t *pipes_arguments);
comparison_t *retrieve_and_or_operator(char *input);
void destroy_comparison(comparison_t *comparison);

#endif
