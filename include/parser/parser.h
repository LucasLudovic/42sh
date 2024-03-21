/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Parser
*/

#ifndef PARSER_H_
    #define PARSER_H_

char **parse_semicolon(char *str);
char **parse_double_left_redirection(char *str);
char **parse_double_right_redirection(char *str, int *fd);
char **parse_single_right_redirection(char *str, int *fd);
char **parse_pipes(char *str);
int check_ambiguity(char **str);

#endif
