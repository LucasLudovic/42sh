/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Complete the user line
*/

#include "my_macros.h"
#include "stddef.h"

static
int check_separator(char character)
{
    if (character == '|' ||
        character == '&' ||
        character == ';')
        return TRUE;
    return FALSE;
}

char *autocomplete_line(char *line)
{
    int is_first_word = TRUE;
    int start_line = 0;
    char *new_line = line;

    if (line == NULL)
        return NULL;
    while (line[start_line] == ' ')
        start_line += 1;
    for (size_t i = start_line; line[i] != '\0'; i += 1) {
        if (is_first_word == FALSE)
            is_first_word = check_separator(line[i]);
        if (is_first_word == TRUE && line[i] == ' ')
            is_first_word = FALSE;
        if (is_first_word == TRUE) {
            i += 1;
            while (line[i] == ' ')
                i += 1;
        }
    }
    if (is_first_word == TRUE)
        return line;
    return new_line;
}
