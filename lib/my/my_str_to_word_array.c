/*
** EPITECH PROJECT, 2023
** MY_STR_TO_WORD_ARRAY
** File description:
** Split a string into words
*/

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "my.h"

static
int check_not_delim(char const str, char const delim)
{
    int condition1 = str < delim || str > delim;

    if (condition1)
        return 0;
    return 1;
}

static
int get_word_length(char const *str)
{
    int i = 0;
    int j = 0;

    while (1) {
        while (str[j] != ' ' && str[j] != '\n' && str[j] != '\0') {
            i += 1;
            j += 1;
        }
        if (i > 0)
            return i;
        j += 1;
    }
}

static
int get_nb_of_words(char const *str, char const delim)
{
    int words = 0;
    int condition1 = 0;
    int condition2 = 0;

    if (str == NULL)
        return -1;
    for (int i = 1; str[i] != '\0'; i += 1) {
        condition1 = check_not_delim(str[i], delim);
        condition2 = check_not_delim(str[i - 1], delim);
        if ((condition1 && !condition2))
            words += 1;
    }
    if (check_not_delim(str[my_strlen(str) - 1], delim) == 0)
        words += 1;
    return words;
}

static
int go_to_word(char **arr)
{
    int nb_spaces = 0;

    while (**arr == ' ') {
        nb_spaces += 1;
        *arr += 1;
    }
    return 0;
}

static
int divide_into_array(char **ptr_to_return, char *arr, int number_of_words)
{
    int word_length = 0;
    int nb_spaces = 0;

    for (int i = 0; i < number_of_words; i += 1) {
        if (go_to_word(&arr) == 84)
            return 84;
        word_length = get_word_length(arr);
        ptr_to_return[i] = malloc(sizeof(char) * (word_length + 1));
        for (int j = 0; j < word_length; j += 1)
            ptr_to_return[i][j] = arr[j];
        ptr_to_return[i][word_length] = '\0';
        arr += word_length;
    }
    return 0;
}

static
char *clean_string(char *str)
{
    char *new_string = NULL;
    int size_string = 0;
    int clean_index = 0;

    if (str == NULL)
        return NULL;
    size_string = my_strlen(str);
    if (str <= 0)
        return NULL;
    new_string = malloc(sizeof(char) * size_string + 1);
    if (new_string == NULL)
        return NULL;
    for (int i = 0; str[i] != '\0'; i += 1)
        if (str[i] != ' ' ||
            (str[i + 1] != ' ' && str[i + 1] != '\0' && str[i + 1] != '\n')) {
            new_string[clean_index] = str[i];
            clean_index += 1;
        }
    new_string[clean_index] = '\0';
    return new_string;
}

char **my_str_to_word_array(char *tab)
{
    int number_of_words = 0;
    char *arr = clean_string(tab);
    char **ptr_to_return = NULL;

    number_of_words = get_nb_of_words(arr, ' ');
    if (number_of_words < 1)
        return NULL;
    ptr_to_return = malloc(sizeof(char *) * (number_of_words + 1));
    if (ptr_to_return == NULL)
        return NULL;
    if (arr == NULL || number_of_words < 1) {
        free(ptr_to_return);
        return NULL;
    }
    if (divide_into_array(ptr_to_return, arr, number_of_words) == 84)
        return NULL;
    ptr_to_return[number_of_words] = NULL;
    if (arr != NULL)
        free(arr);
    return ptr_to_return;
}
