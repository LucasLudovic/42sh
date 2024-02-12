/*
** EPITECH PROJECT, 2023
** MY_GETNBR
** File description:
** Convert a string to a number
*/

static
int check_if_number(char character, long numberToReturn)
{
    if (character < '0' || character > '9') {
        if (numberToReturn != 0)
            return 0;
        if (character == '-' || character == '+')
            return 1;
        return 0;
    } else
        return 1;
}

static
int check_length(long number, const char *str)
{
    if (number > 2147483647 || number < -2147483648)
        return 0;
    if (number == -1) {
        str -= 2;
        if (*str != '-')
            return 0;
        str += 1;
        if (*str != '1')
            return 0;
        str += 1;
        if (*str != '\0')
            return 0;
    }
    return number;
}

static
void suppress_line(long int *numberToReturn, const char *str)
{
    *numberToReturn *= 10;
    *numberToReturn += *str - 48;
}

static
void suppress_other_line(int *negativ, const char **str)
{
    *str += 1;
    *negativ *= -1;
}

int my_getnbr(char const *str)
{
    long numberToReturn = 0;
    int negativ = 1;

    if (str == 0)
        return 0;
    while (*str != '\0') {
        if (check_if_number(*str, numberToReturn) == 0)
            return check_length(numberToReturn * negativ, str);
        if (*str == '-' && numberToReturn == 0) {
            suppress_other_line(&negativ, &str);
            continue;
        }
        if (*str == '+') {
            str += 1;
            continue;
        }
        suppress_line(&numberToReturn, str);
        str += 1;
    }
    return check_length(numberToReturn * negativ, str);
}
