/*
** EPITECH PROJECT, 2024
** Builtin
** File description:
** Header to for my builtin function pointers array
*/

#ifndef BUILTIN_H_
    #define BUILTIN_H_
    #include "shell/my_shell.h"

typedef struct builtin_s {
    char *name[6];
    int (*function[6])(shell_t *, char **, int);
} builtin_t;

#endif
