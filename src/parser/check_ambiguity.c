/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Check redirections ambiguity
*/

#include <stddef.h>
#include "my.h"

static
void update_double_left(char **str, int *double_left, size_t *i, size_t *j)
{
    if (str == NULL || str[*i] == NULL)
        return;
    if (str[*i][*j] == '<' && str[*i][*j + 1] == '<') {
        *double_left += 1;
        *j += 1;
    }
}

static
void update_double_right(char **str, int *double_right, size_t *i, size_t *j)
{
    if (str == NULL || str[*i] == NULL)
        return;
    if (str[*i][*j] == '>' && str[*i][*j + 1] == '>') {
        *double_right += 1;
        *j += 1;
    }
}

static
void update_simple_right(char **str, int *simple_right, size_t *i, size_t j)
{
    if (str == NULL || str[*i] == NULL)
        return;
    if (str[*i][j] == '>' && str[*i][j + 1] != '>') {
        *simple_right += 1;
    }
}

static
void update_simple_left(char **str, int *simple_left, size_t *i, size_t j)
{
    if (str == NULL || str[*i] == NULL)
        return;
    if (str[*i][j] == '<' && str[*i][j + 1] != '<') {
        *simple_left += 1;
    }
}

static
int check_number(int *double_right, int *double_left,
    int *simple_right, int *simple_left)
{
    if (*double_right > 1 || *simple_right > 1) {
        my_putstr("Ambiguous output redirect.\n");
        return TRUE;
    }
    if (*double_left > 1 || *simple_left > 1) {
        my_putstr("Ambiguous input redirect.\n");
        return TRUE;
    }
    *double_right = 0;
    *double_left = 0;
    *simple_right = 0;
    *simple_left = 0;
    return FALSE;
}

int check_ambiguity(char **str)
{
    int double_right = 0;
    int double_left = 0;
    int simple_left = 0;
    int simple_right = 0;

    if (str == NULL)
        return FAILURE;
    for (size_t i = 0; str[i] != NULL; i += 1) {
        for (size_t j = 0; str[i][j] != '\0'; j += 1) {
            update_simple_left(str, &simple_left, &i, j);
            update_simple_right(str, &simple_right, &i, j);
            update_double_right(str, &double_right, &i, &j);
            update_double_left(str, &double_left, &i, &j);
        }
        if (check_number(&double_right, &double_left,
            &simple_right, &simple_left) == TRUE)
            return TRUE;
    }
    return FALSE;
}
