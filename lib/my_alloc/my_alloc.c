/*
** EPITECH PROJECT, 2024
** Alloc
** File description:
** Alloc function from the libc
*/

#include <stddef.h>
#include <stdlib.h>

void *my_memcpy(void *dest, void *src, size_t size)
{
    char *dest_cpy = NULL;
    char *src_cpy = NULL;

    if (dest == NULL || src == NULL)
        return dest;
    dest_cpy = (char *)dest;
    src_cpy = (char *)src;
    for (size_t i = 0; i < size; i += 1)
        dest_cpy[i] = src_cpy[i];
    return dest_cpy;
}

void *my_realloc(void *pointer, size_t size_final, size_t size_initial)
{
    char *new_pointer = NULL;

    if (pointer == NULL)
        return malloc(sizeof(char) * size_final);
    if (size_final == 0) {
        free(pointer);
        return NULL;
    }
    new_pointer = malloc(sizeof(char) * size_final);
    if (new_pointer == NULL)
        return pointer;
    if (size_final < size_initial)
        new_pointer = my_memcpy(new_pointer, pointer, size_final);
    else
        new_pointer = my_memcpy(new_pointer, pointer, size_initial);
    if (new_pointer == NULL)
        return pointer;
    free(pointer);
    return new_pointer;
}
