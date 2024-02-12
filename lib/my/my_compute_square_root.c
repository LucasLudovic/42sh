/*
** EPITECH PROJECT, 2023
** MY_COMPUTE_SQUARE_ROOT
** File description:
** Compute the square root
*/

int my_compute_square_root(int nb)
{
    long long_number = nb;
    int number_to_return;

    if (nb == 1)
        return 1;
    if (long_number > 2147483647 || long_number < 0)
        return 0;
    for (int i = 0; i < long_number / 2 + 1; i += 1) {
        if (i * i == long_number) {
            number_to_return = i;
            return number_to_return;
        }
    }
    return 0;
}
