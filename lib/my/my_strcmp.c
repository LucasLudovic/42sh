/*
** EPITECH PROJECT, 2023
** MY_STRCMP
** File description:
** Compare if a string is greater than the other
*/

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    for (i = 0; s1[i] != '\0'; i += 1) {
        if (s2[i] == '\0')
            return (s1[i] - s2[i]);
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
    }
    if (s2[i] != '\0')
        return (-1 * s2[i]);
    return 0;
}
