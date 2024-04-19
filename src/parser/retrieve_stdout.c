/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** retrieve_stdout.c
*/

#include <unistd.h>

void retrieve_stdout(int *output_fd, int *save_stdout)
{
    if (*output_fd != STDOUT_FILENO) {
        dup2(*save_stdout, STDOUT_FILENO);
        close(*output_fd);
        close(*save_stdout);
    }
}
