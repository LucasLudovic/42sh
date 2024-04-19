/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** retrieve_stdin.c
*/

#include <unistd.h>

void retrieve_stdin(int *input_fd, int *save_input)
{
    if (*input_fd != STDIN_FILENO) {
        dup2(*save_input, STDIN_FILENO);
        close(*input_fd);
        close(*save_input);
    }
}
