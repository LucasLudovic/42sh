/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Adding the pipe function
*/

#include <stdlib.h>
#include <unistd.h>
#include "actions/execute_actions.h"
#include "builtin/builtin.h"
#include "parser/parser.h"
#include "my.h"
#include "my_macros.h"
#include "my_alloc.h"

static
void split_arguments(pipes_splits_t *pipes_split, char **arguments)
{
    if (pipes_split == NULL || arguments == NULL)
        return;
    for (size_t i = 0; arguments[i] != NULL; i += 1) {
        if (my_strcmp(arguments[i], "|") == 0) {
            free(arguments[i]);
            arguments[i] = NULL;
            if (arguments[i + 1] != NULL) {
                pipes_split->next = malloc(sizeof(pipes_splits_t));
                pipes_split->next->arguments = &(arguments[i + 1]);
                pipes_split->next->next = NULL;
                pipes_split->path = NULL;
                pipes_split = pipes_split->next;
            }
        }
    }
}

pipes_splits_t *parse_pipes(char **arguments)
{
    pipes_splits_t *pipes_split = NULL;

    if (arguments == NULL)
        return NULL;
    pipes_split = malloc(sizeof(pipes_splits_t));
    if (pipes_split == NULL)
        return NULL;
    pipes_split->arguments = arguments;
    pipes_split->next = NULL;
    pipes_split->path = NULL;
    split_arguments(pipes_split, arguments);
    return pipes_split;
}

