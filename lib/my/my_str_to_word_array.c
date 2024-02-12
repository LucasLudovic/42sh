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
int my_isalphanum(char const str)
{
    int condition1 = str < 48 || str > 57;
    int condition2 = str < 65 || str > 90;
    int condition3 = str < 97 || str > 122;

    if (condition1 && condition2 && condition3)
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
int get_nb_of_words(char const *str)
{
    int words = 0;
    int condition1 = 0;
    int condition2 = 0;
    int condition3 = 0;
    int condition4 = 0;

    for (int i = 1; str[i] != '\0'; i += 1) {
        condition1 = my_isalphanum(str[i]);
        condition2 = my_isalphanum(str[i - 1]);
        condition3 = str[i] == '.';
        condition4 = str[i - 1] == '.';
        if ((!condition1 && condition2) || (!condition3 && condition4))
            words += 1;
    }
    if (my_isalphanum(str[my_strlen(str) - 1]) ||
        str[my_strlen(str) - 1] == '.')
        words += 1;
    return words;
}

static
int go_to_word(char **arr)
{
    int nb_spaces = 0;

    while (**arr == ' ') {
        if (nb_spaces > 0)
            return 84;
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

char **my_str_to_word_array(char *tab)
{
    int number_of_words = get_nb_of_words(tab);
    char *arr = tab;
    char **ptr_to_return = malloc(sizeof(char *) * (number_of_words + 1));

    if (ptr_to_return == NULL)
        return NULL;
    if (arr == NULL) {
        free(ptr_to_return);
        return NULL;
    }
    if (divide_into_array(ptr_to_return, arr, number_of_words) == 84)
        return NULL;
    ptr_to_return[number_of_words] = NULL;
    return ptr_to_return;
}
