/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Display the logo for the 42sh project
*/

#include "shell/my_shell.h"
#include "my.h"

static
const char logo[] =
" $$$$$$\\  $$\\                                               $$\\   $$\\  $"
"$$$$$\\                $$\\                               $$\\       \n"
"$$  __$$\\ $$ |                                              $$ |  $$ |$$$ _"
"_$$\\               $$ |                              $$ |      \n"
"$$ /  $$ |$$$$$$$\\          $$$$$$\\$$$$\\  $$\\   $$\\         $$ |  $$ |$"
"$$$\\ $$ |         $$$$$$$ | $$$$$$\\  $$\\   $$\\  $$$$$$$\\ $$$$$$$\\  \n"
"$$ |  $$ |$$  __$$\\ $$$$$$\\ $$  _$$  _$$\\ $$ |  $$ |$$$$$$\\ $$$$$$$$ |$$"
"\\$$\\$$ |$$$$$$\\ $$  __$$ |$$  __$$\\ $$ |  $$ |$$  _____|$$  __$$\\ \n"
"$$ |  $$ |$$ |  $$ |\\______|$$ / $$ / $$ |$$ |  $$ |\\______|\\_____$$ |$$ "
"\\$$$$ |\\______|$$ /  $$ |$$$$$$$$ |$$ |  $$ |\\$$$$$$\\  $$ |  $$ |\n"
"$$ |  $$ |$$ |  $$ |        $$ | $$ | $$ |$$ |  $$ |              $$ |$$ |\\"
"$$$ |        $$ |  $$ |$$   ____|$$ |  $$ | \\____$$\\ $$ |  $$ |\n"
" $$$$$$  |$$ |  $$ |        $$ | $$ | $$ |\\$$$$$$$ |              $$ |\\$$$"
"$$$  /        \\$$$$$$$ |\\$$$$$$$\\ \\$$$$$$  |$$$$$$$  |$$ |  $$ |\n"
" \\______/ \\__|  \\__|        \\__| \\__| \\__| \\____$$ |              \\_"
"_| \\______/          \\_______| \\_______| \\______/ \\_______/ \\__|  \\__"
"|\n"
"                                          $$\\   $$ |                       "
"                                                               \n"
"                                          \\$$$$$$  |                       "
"                                                               \n"
"                                           \\______/                        "
"                                                               \n";

static
const char delim[] = " ______________________________________________________"
"________________________________________________________________________"
"____________\n"
"/_____/_____/_____/_____/_____/_____/_____/_____/_____/_____/"
"_____/_____/_____/_____/_____/_____/_____/_____/_____/_____/_____/_____/"
"_____/\n";

void display_logo(void)
{
    if (check_if_tty())
        return;
    display_string_colored(delim, "blue");
    display_string_colored(logo, "green");
    display_string_colored(delim, "blue");
}
