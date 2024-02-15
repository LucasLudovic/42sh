/*
** EPITECH PROJECT, 2024
** Alias
** File description:
** Header for alias
*/

#ifndef ALIAS_H_
    #define ALIAS_H_

typedef struct alias_s {
    char *initial_name;
    char *alias;
    struct alias_s *next;
} alias_t;

int change_name(char **arguments);
char *check_alias(alias_t *alias, char *arguments);

#endif
