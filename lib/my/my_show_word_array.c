/*
** EPITECH PROJECT, 2023
** MY_SHOW_WORD_ARRAY
** File description:
** Display content of array of words
*/

#include "my.h"

static
int get_array_size(char const **tab)
{
    int i = 0;

    while (tab[i] != 0) {
        i += 1;
    }
    return i;
}

int my_show_word_array(char const **tab)
{
    int size = get_array_size(tab);

    for (int i = 0; i < size; i += 1) {
        my_putstr(tab[i]);
        my_putchar('\n');
    }
    return 0;
}
