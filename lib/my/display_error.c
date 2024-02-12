/*
** EPITECH PROJECT, 2023
** Display error
** File description:
** Display an error and return 84
*/

#include <unistd.h>
#include "my.h"

int display_error(char *error)
{
    int i = 0;

    while (error[i] != '\0') {
        write(2, &error[i], 1);
        i += 1;
    }
    return 84;
}
