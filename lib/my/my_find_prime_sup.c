/*
** EPITECH PROJECT, 2023
** MY_FIND_PRIME_SUP
** File description:
** return the smallest prime number greater than its parameter
*/

static
int check_is_prime(int nb)
{
    long long_number = nb;

    if (long_number > 2147483647 || long_number < 2)
        return 0;
    for (int i = 2; i < nb / 2 +1; i += 1) {
        if (nb % i == 0)
            return 0;
    }
    return 1;
}

int my_find_prime_sup(int nb)
{
    long long_nb = nb;

    if (long_nb > 2147483647 || long_nb < -2147483648)
        return 0;
    if (long_nb <= 2)
        return 2;
    for (int i = nb; i < 2147483647; i += 1) {
        if (check_is_prime(i) == 1)
            return i;
    }
    if (long_nb == 2147483647)
        return long_nb;
    return 0;
}
