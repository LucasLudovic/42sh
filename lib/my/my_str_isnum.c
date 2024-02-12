/*
** EPITECH PROJECT, 2023
** MY_STR_ISNUM
** File description:
** Check if a string is all digit
*/

int my_str_isnum(char const *str)
{
    int condition1 = 0;

    for (int i = 0; str[i] != '\0'; i += 1) {
        condition1 = str[i] < '0' || str[i] > '9';
        if (condition1)
            return 0;
    }
    return 1;
}
