/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Double_left_redirection
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "my_alloc.h"
#include "my.h"

static
size_t compare_user_input(char *pattern, size_t address_parsed)
{
    char *user_input = NULL;
    size_t size = 0;

    if (pattern == NULL)
        return 0;
    while (TRUE) {
        my_putstr("? ");
        if (getline(&user_input, &size, stdin) <= 0)
            return -1;
        if (user_input == NULL)
            return -1;
        if (user_input[my_strlen(user_input) - 1] == '\n')
            user_input[my_strlen(user_input) - 1] = '\0';
        if (my_strncmp(user_input, pattern, my_strlen(user_input)) == 0
            && my_strlen(user_input) == my_strlen(pattern))
            return address_parsed;
    }
    return 0;
}

static
void update_pattern(char *pattern, char *str, int *character_added, int index)
{
    if (pattern == NULL || str == NULL || character_added == NULL)
        return;
    pattern[*character_added] = str[index];
    pattern[*character_added + 1] = '\0';
    *character_added += 1;
}

static
int search_pattern(char *str)
{
    char *pattern = NULL;
    int character_added = 0;
    size_t address_parsed = 0;

    if (str == NULL || str[0] == '\0')
        return 0;
    for (size_t i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == ' ' && pattern == NULL)
            continue;
        if (str[i] == ' ')
            break;
        if (pattern == NULL)
            pattern = malloc(sizeof(char) * (my_strlen(str) + 1));
        if (pattern == NULL)
            return -1;
        update_pattern(pattern, str, &character_added, i);
        address_parsed = i + 1;
    }
    return compare_user_input(pattern, address_parsed);
}

static
int check_single_character(char *str, size_t i)
{
    int pattern_found = 0;

    if (str[i] == '<' && str[i + 1] == '<') {
        pattern_found = search_pattern(&str[i + 2]);
        if (pattern_found < 0)
            return FAILURE;
        if (pattern_found == 0)
            return SUCCESS;
        str[i] = ' ';
        my_strcpy(&str[i + 1], &str[i + 2 + pattern_found]);
    }
    return SUCCESS;
}

int parse_double_left_redirection(char *str)
{
    if (str == NULL)
        return FAILURE;
    if (str[my_strlen(str) - 1] == '\n')
        str[my_strlen(str) - 1] = '\0';
    for (size_t i = 0; str[i] != '\0'; i += 1) {
        if (check_single_character(str, i) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}
