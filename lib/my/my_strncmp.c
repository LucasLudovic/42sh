/*
** EPITECH PROJECT, 2023
** MY_STRNCMP
** File description:
** Compare if a string is greater than the other for a size n
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    for (i = 0; s1[i] != '\0' && i < n; i += 1) {
        if (s2[i] == '\0')
            return (s1[i] - s2[i]);
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
    }
    return 0;
}
