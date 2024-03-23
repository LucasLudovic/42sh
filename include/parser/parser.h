/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Parser
*/

#ifndef PARSER_H_
    #define PARSER_H_

typedef struct pipes_split_s {
    char **arguments;
    char *path;
    struct pipes_split_s *next;
} pipes_splits_t;

char **parse_semicolon(char *str);
char **parse_double_left_redirection(char *str);
char **parse_double_right_redirection(char *str, int *fd);
char **parse_single_right_redirection(char *str, int *fd);
pipes_splits_t *parse_pipes(char **arguments);
int check_ambiguity(char **str);

#endif
