/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Retrieve the && and || operators
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "shell/my_shell.h"
#include "parser/parser.h"

void destroy_comparison(comparison_t *comparison)
{
    if (comparison == NULL)
        return;
    destroy_comparison(comparison->next);
    free(comparison);
}

static
void add_new_node(comparison_t *comparison, char *input, char comparator)
{
    comparison_t *current = NULL;

    if (comparison == NULL)
        return;
    comparison->next = malloc(sizeof(comparison_t));
    current = comparison->next;
    current->argument = input;
    current->previous_comparator = comparator;
    current->next = NULL;
}

comparison_t *retrieve_and_or_operator(shell_t *shell, char *input)
{
    comparison_t *comparison = malloc(sizeof(comparison_t));
    comparison_t *head = comparison;

    if (comparison == NULL) {
        display_error("Unable to alloc memory to comparison\n");
        return NULL;
    }
    if (shell == NULL || input == NULL) {
        display_error("Unable to retrieve structs with && operator\n");
        free(comparison);
        return NULL;
    }
    comparison->argument = input;
    comparison->previous_comparator = NO_COMPARATOR;
    comparison->next = NULL;
    for (size_t i = 0; input[i] != '\0'; i += 1) {
        if (comparison == NULL) {
            display_error("Unable to access comparison\n");
            return destroy_comparison(head), NULL;
        }
        if (input[i] == '&' && input[i + 1] == '&') {
            input[i] = '\0';
            add_new_node(comparison, &input[i + 2], AND);
            comparison = comparison->next;
        }
        if (input[i] == '|' && input[i + 1] == '|') {
            input[i] = '\0';
            add_new_node(comparison, &input[i + 2], OR);
            comparison = comparison->next;
        }
    }
    return head;
}
