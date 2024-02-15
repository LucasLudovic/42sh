/*
** EPITECH PROJECT, 2024
** Alloc
** File description:
** Alloc function from the libc
*/

#include <stdlib.h>

void *my_memcpy(void *dest, void *src, size_t size)
{
    char *dest_cpy = (char *)dest;
    char *src_cpy = (char *)src;

    if (dest == NULL || src == NULL)
        return NULL;
    for (size_t i = 0; i < size; i += 1)
        dest_cpy[i] = src_cpy[i];
    return dest;
}

void *my_realloc(void *pointer, size_t size_final, size_t size_initial)
{
    char *new_pointer = malloc(sizeof(char) * size_final);

    if (new_pointer == NULL)
        return NULL;
    if (pointer == NULL) {
        free(new_pointer);
        return pointer;
    }
    if (size_final < size_initial)
        new_pointer = my_memcpy(new_pointer, pointer, size_final);
    else
        new_pointer = my_memcpy(new_pointer, pointer, size_initial);
    if (new_pointer == NULL)
        return pointer;
    if (pointer != NULL)
        free(pointer);
    return new_pointer;
}
