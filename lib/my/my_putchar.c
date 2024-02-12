/*
** EPITECH PROJECT, 2023
** MY_PUTCHAR
** File description:
** Display a character
*/

#include <stdio.h>
#include <unistd.h>

int my_putchar(char c)
{
    write(1, &c, 1);
    return 0;
}
