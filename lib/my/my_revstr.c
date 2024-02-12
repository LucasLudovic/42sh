/*
** EPITECH PROJECT, 2023
** MY_REVSTR
** File description:
** Reverse a string
*/

char *my_revstr(char *str)
{
    int length = 0;
    char character;

    while (str[length] != '\0') {
        length += 1;
    }
    for (int i = 0; i < length / 2; i += 1) {
        character = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = character;
    }
    return str;
}
