/*
** EPITECH PROJECT, 2023
** MY_SORT_INT_ARRAY
** File description:
** Sort an array of integer
*/

static
void check_sorted(int *condition, int *array, int size)
{
    for (int i = 0; i < size - 1; i ++) {
        if (array[i] > array[i + 1])
            *condition = 0;
    }
}

static
void sort_single_step(int *array, int size)
{
    int previousNumber;

    for (int i = 0; i < size - 1; i += 1) {
        if (array[i] > array[i + 1]) {
            previousNumber = array[i];
            array[i] = array[i + 1];
            array[i + 1] = previousNumber;
        }
    }
}

void my_sort_int_array(int *array, int size)
{
    int condition = 0;

    while (condition == 0) {
        condition = 1;
        sort_single_step(array, size);
        check_sorted(&condition, array, size);
    }
}
