/*
** EPITECH PROJECT, 2023
** MY_COMPUTE_POWER_REC
** File description:
** Recursiv fonction which compute a power
*/

int my_compute_power_rec(int nb, int p)
{
    long long_number = nb;

    if (p == 0)
        return 1;
    if (p < 0)
        return 0;
    if (long_number > 2147483647 || long_number < -2147483648)
        return 0;
    long_number *= my_compute_power_rec(nb, p - 1);
    if (long_number > 2147483647 || long_number < -2147483648)
        return 0;
    nb = long_number;
    return nb;
}
