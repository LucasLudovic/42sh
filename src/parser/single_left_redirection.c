/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Parse the < redirection
*/

#include "my.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static
int write_path_character(char *str, char *file_name, int *character_added,
    int index)
{
    if (file_name == NULL)
        return FAILURE;
    file_name[*character_added] = str[index];
    file_name[*character_added + 1] = '\0';
    *character_added += 1;
    return SUCCESS;
}

static void open_file(int *fd, char *str)
{
    char *file_name = NULL;
    int char_added = 0;

    if (str == NULL || str[0] == '\0' || fd == NULL)
        return;
    for (size_t i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == ' ' && file_name == NULL)
            continue;
        if (str[i] == ' ' || str[i] == '<' || str[i] == '>' || str[i] == '|')
            break;
        if (file_name == NULL)
            file_name = malloc(sizeof(char) * (my_strlen(str) + 1));
        if (write_path_character(str, file_name, &char_added, i) == FAILURE)
            return;
    }
    if (file_name[my_strlen(file_name) - 1] == '\n')
        file_name[my_strlen(file_name) - 1] = '\0';
    *fd = open(file_name, O_RDONLY);
    free(file_name);
}

char *parse_single_left_redirection(char *str, int *fd)
{
    if (str == NULL)
        return str;
    for (size_t i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == '<' && str[i + 1] != '<') {
            str[i] = '\0';
            open_file(fd, &str[i + 1]);
            return str;
        }
    }
    return str;
}
