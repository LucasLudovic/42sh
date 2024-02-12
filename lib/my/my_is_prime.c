/*
** EPITECH PROJECT, 2023
** MY_IS_PRIME
** File description:
** Check if a number is prime
*/

int my_is_prime(int nb)
{
    long long_number = nb;

    if (long_number > 2147483647 || nb < 2)
        return 0;
    for (int i = 2; i < nb / 2 +1; i += 1) {
        if (nb % i == 0)
            return 0;
    }
    return 1;
}
