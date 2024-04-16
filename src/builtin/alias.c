/*
** EPITECH PROJECT, 2024
** Alias
** File description:
** Give an alias to a command
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "builtin/alias.h"
#include "my.h"
#include "my_macros.h"
#include "shell/my_shell.h"

static
void display_alias(alias_t *alias)
{
    if (alias == NULL) {
        printf("No alias to display\n");
        return;
    }
    while (alias != NULL) {
        if (alias->alias == NULL || alias->initial_name == NULL)
            break;
        printf("%s='%s'\n", alias->alias, alias->initial_name);
        alias = alias->next;
    }
}

static
int get_alias(alias_t *alias, char *argument)
{
    int end_alias_name = 0;

    if (alias == NULL)
        return FAILURE;
    for (size_t i = 0; argument[i] != '\0'; i += 1){
        if (argument[i] == '=') {
            end_alias_name = i;
            alias->alias = my_strdup(argument);
            break;
        }
    }
    if (end_alias_name == 0)
        return display_error("Alias wrong format\n");
    if (alias->alias == NULL) {
        display_error("Unable to alloc memory to alias initial name\n");
        return FAILURE;
    }
    alias->alias[end_alias_name] = '\0';
    return SUCCESS;
}

static
int get_initial_name(alias_t *alias, char *argument)
{
    int end_initial_name = 0;

    if (alias == NULL)
        return FAILURE;
    for (size_t i = 0; argument[i] != '\0'; i += 1){
        if (argument[i] == '=') {
            end_initial_name = i;
            alias->initial_name = my_strdup(&argument[i + 1]);
            break;
        }
    }
    if (end_initial_name == 0)
        return display_error("Alias wrong format\n");
    if (alias->initial_name == NULL)
        return display_error("Unable to alloc memory to alias name\n");
    return SUCCESS;
}

static
int check_alias_already_present(alias_t *alias, char *argument)
{
    char *new_alias = my_strdup(strtok(argument, "="));
    char *new_initial_name = my_strdup(strtok(NULL, "="));

    if (argument != NULL)
        free(argument);
    if (new_alias == NULL || new_initial_name == NULL) {
        if (new_alias != NULL)
            free(new_alias);
        return FALSE;
    }
    if (strcmp(alias->alias, new_alias) == 0) {
        if (alias->initial_name != NULL)
            free(alias->initial_name);
        alias->initial_name = new_initial_name;
        if (new_alias != NULL)
            free(new_alias);
        return TRUE;
    }
    free(new_alias);
    free(new_initial_name);
    return FALSE;
}

static
int add_new_alias(alias_t *alias, char *argument)
{
    if (alias == NULL || argument == NULL)
        return FAILURE;
    while (alias->next != NULL) {
        if (check_alias_already_present(alias, strdup(argument)) == TRUE)
            return SUCCESS;
        alias = alias->next;
    }
    if (check_alias_already_present(alias, strdup(argument)) == TRUE)
        return SUCCESS;
    alias->next = malloc(sizeof(alias_t));
    if (alias->next == NULL)
        return display_error("Unable to alloc memory to new alias\n");
    alias->next->next = NULL;
    alias->next->alias = NULL;
    alias->next->initial_name = NULL;
    if (get_alias(alias->next, argument) == FAILURE
        || get_initial_name(alias->next, argument) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

alias_t *destroy_alias(alias_t *alias)
{
    if (alias == NULL)
        return NULL;
    destroy_alias(alias->next);
    if (alias->initial_name != NULL)
        free(alias->initial_name);
    if (alias->alias != NULL)
        free(alias->alias);
    free(alias);
    return NULL;
}

int replace_alias(shell_t *shell, char **arguments, int nb_arguments)
{
    if (shell == NULL || arguments == NULL)
        return FAILURE;
    if (nb_arguments > 2)
        return display_error("Wrong number of arguments\n");
    if (arguments[0] != NULL && arguments[1] == NULL) {
        display_alias(shell->alias);
        return SUCCESS;
    }
    if (shell->alias == NULL) {
        shell->alias = malloc(sizeof(alias_t));
        if (shell->alias == NULL)
            return display_error("Unable to initialize alias");
        if (get_alias(shell->alias, arguments[1]) == FAILURE
            || get_initial_name(shell->alias, arguments[1]) == FAILURE)
            return FAILURE;
        shell->alias->next = NULL;
        return SUCCESS;
    }
    add_new_alias(shell->alias, arguments[1]);
    return SUCCESS;
}
