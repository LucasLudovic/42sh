/*
** EPITECH PROJECT, 2023
** MY_STRNCAT
** File description:
** Concatenate n character
*/

static
int get_length(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        i += 1;
    return i;
}

static
char *my_new_strncpy(char *dest, char const *src, int n)
{
    int counter;

    for (counter = 0; counter < n; counter += 1) {
        dest[counter] = src[counter];
        if (src[counter] == '\0')
            return dest;
    }
}

char *my_strncat(char *dest, char const *src, int nb)
{
    my_new_strncpy(dest + get_length(dest), src, nb);
    return dest;
}
