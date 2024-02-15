/*
** EPITECH PROJECT, 2024
** Alloc
** File description:
** Header for my alloc functions inspired by the libc
*/

#ifndef MY_ALLOC_H_
    #define MY_ALLOC_H_
    #include <stddef.h>

void *my_memcpy(void *dest, void *src, size_t size);
void *my_realloc(void *pointer, size_t size_final, size_t size_initial);

#endif
