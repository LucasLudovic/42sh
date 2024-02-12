/*
** EPITECH PROJECT, 2023
** MY_STRLEN
** File description:
** Return the size of a string
*/

int my_strlen(char const *str)
{
    char const *ptr = str;
    int counter = 0;

    while (*ptr != '\0') {
        counter += 1;
        ptr += 1;
    }
    return counter;
}
