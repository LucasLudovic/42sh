/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** handles segfaults
*/

#include <signal.h>
#include <stdlib.h>
#include <dirent.h>
#include <threads.h>
#include <unistd.h>
#include <sys/wait.h>
#include "my.h"
#include <stdbool.h>
#include <sys/stat.h>
#include <stdio.h>

int check_dump(int wait_status)
{
    if (WCOREDUMP(wait_status)) {
        display_error(" (core dumped)\n");
        return wait_status;
    }
    return 0;
}
