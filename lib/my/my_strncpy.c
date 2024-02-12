/*
** EPITECH PROJECT, 2023
** MY_STRNCPY
** File description:
** Copy n character from a string
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    int counter;

    for (counter = 0; counter < n; counter += 1) {
        dest[counter] = src[counter];
        if (src[counter] == '\0')
            return dest;
    }
}
