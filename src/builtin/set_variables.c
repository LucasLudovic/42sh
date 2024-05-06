/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** set_variables.c
*/

#include "my.h"
#include "my_macros.h"
#include "shell/my_shell.h"
#include <stdio.h>

int set(shell_t *shell, char **arguments, UNUSED int nb_arguments)
{
    printf("set\n");
    return SUCCESS;
}
