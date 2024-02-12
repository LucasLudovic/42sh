/*
** EPITECH PROJECT, 2023
** MY_STR_ISLOWER
** File description:
** Check if only lower and alpha
*/

int my_str_islower(char const *str)
{
    int condition = 0;

    for (int i = 0; str[i] != 0; i += 1) {
        condition = str[i] < 97 || str[i] > 122;
        if (condition)
            return 0;
    }
    return 1;
}
