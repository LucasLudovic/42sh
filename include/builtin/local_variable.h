/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** local_variable.h
*/

#ifndef LOCAL_VARIABLE_H_
    #define LOCAL_VARIABLE_H_

typedef struct variable {
    char *name;
    char *value;
    struct variable *next;
} variable_t;

#endif
