/*
** EPITECH PROJECT, 2023
** MY_STR_ISALPHA
** File description:
** Write 1 if only alphabet character
*/

int my_str_isalpha(char const *str)
{
    int i = 0;
    int condition1 = 0;
    int condition2 = 0;

    while (str[i] != '\0') {
        condition1 = str[i] < 65 || str[i] > 90;
        condition2 = str[i] < 97 || str[i] > 122;
        if (condition1 && condition2)
            return 0;
        i += 1;
    }
    return 1;
}
