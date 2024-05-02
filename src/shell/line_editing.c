/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** File to edit the line of the input user
*/

#include <termio.h>
#include <unistd.h>
#include "my.h"

int initialise_termios(void)
{
    struct termios old_terminal = { 0 };
    struct termios new_terminal = { 0 };

    tcgetattr(STDIN_FILENO , &old_terminal);
    new_terminal = old_terminal;
    new_terminal.c_lflag &=(~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO , TCSANOW , &new_terminal);
    return SUCCESS;
}
