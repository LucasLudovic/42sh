/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Parse double right redirection
*/

#include <stdlib.h>
#include <fcntl.h>
#include "my.h"

static
void open_redirection_fd(char *str, int *fd)
{
    char *file_name = NULL;
    int character_added = 0;

    if (str == NULL || str[0] == '\0' || fd == NULL)
        return;
    for (size_t i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == ' ' && file_name == NULL)
            continue;
        if (str[i] == ' ' || str[i] == '<' || str[i] == '>' || str[i] == '|')
            break;
        if (file_name == NULL)
            file_name = malloc(sizeof(char) * (my_strlen(str) + 1));
        if (file_name == NULL)
            return;
        file_name[character_added] = str[i];
        file_name[character_added + 1] = '\0';
        character_added += 1;
    }
    printf("File_name : %s\n", file_name);
    *fd = open(file_name, O_RDWR | O_CREAT, S_IROTH | S_IWOTH);
    printf("Bijour : %i\n", *fd);
    free(file_name);
}

char *parse_double_right_redirection(char *str, int *fd)
{
    if (str == NULL || fd == NULL)
        return str;
    for (size_t i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == '>' && str[i + 1] == '>') {
            str[i] = '\0';
            open_redirection_fd(&str[i + 2], fd);
            return str;
        }
    }
    return str;
}
