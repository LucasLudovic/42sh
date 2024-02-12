/*
** EPITECH PROJECT, 2023
** MY_SWAP
** File description:
** Swap two integer
*/

void my_swap(int *a, int *b)
{
    int c;

    c = *a;
    *a = *b;
    *b = c;
}
