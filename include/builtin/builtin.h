/*
** EPITECH PROJECT, 2024
** Builtin
** File description:
** Header to for my builtin function pointers array
*/

#ifndef BUILTIN_H_
    #define BUILTIN_H_
    #include "my_macros.h"
    #include "shell/my_shell.h"

typedef struct builtin_s {
    char *name[NB_BUILTIN];
    int (*function[NB_BUILTIN])(shell_t *, char **, int);
} builtin_t;

void empty_buffer(void);

#endif
