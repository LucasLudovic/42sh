/*
** EPITECH PROJECT, 2024
** history
** File description:
** Header to get the user history for the 42sh project
*/

#ifndef HISTORY_STRUCT_H_
    #define HISTORY_STRUCT_H_

typedef struct history_s {
    int index;
    char *cmd;
    char *time;
    struct history_s *next;
} history_t;

#endif
