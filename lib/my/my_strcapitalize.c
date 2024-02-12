/*
** EPITECH PROJECT, 2023
** MY_STRCAPITALIZE
** File description:
** First letter of each word to upper
*/

static
char *my_lowcase(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] >= 65 && str[i] <= 90)
            str[i] += 32;
        i += 1;
    }
    return str;
}

char *my_strcapitalize(char *str)
{
    int condition1 = 0;
    int condition2 = 0;
    int condition3 = 0;

    str = my_lowcase(str);
    if (str[0] >= 97 && str[0] <= 122)
        str[0] -= 32;
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (i == 0)
            continue;
        condition1 = (str[i - 1] < 97 || str[i - 1] > 122);
        condition2 = (str[i - 1] < 65 || str[i - 1] > 90);
        condition3 = str[i] >= 97 && str[i] <= 122;
        if (condition1 && condition2 && condition3)
            str[i] -= 32;
    }
    return str;
}
