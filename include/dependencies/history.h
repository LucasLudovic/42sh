/*
** EPITECH PROJECT, 2024
** history
** File description:
** Header to get the user history for the minishell1 project
*/

#ifndef HISTORY_H_
    #define HISTORY_H_

typedef struct history_s {
    char *cmd;
    struct history_s *next;
} history_t;

#endif
