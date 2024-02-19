/*
** EPITECH PROJECT, 2024
** Environment array
** File description:
** Convert the environment to an array for the minishell project
*/

#include <stdlib.h>
#include "dependencies/environment.h"
#include "my.h"

static
int get_environment_length(environment_t *environment)
{
    int length = 0;

    while (environment != NULL) {
        length += 1;
        environment = environment->next;
    }
    return length;
}

static
char *add_single_variable(environment_t *environment, char **array, int pos)
{
    int key_size = 0;
    int value_size = 0;

    if (environment == NULL || environment->key == NULL)
        return NULL;
    key_size = my_strlen(environment->key);
    if (environment->value != NULL)
        value_size = my_strlen(environment->value);
    array[pos] = malloc(sizeof(char) * (key_size + value_size + 2));
    if (array[pos] == NULL)
        return NULL;
    if (my_strcpy(array[pos], environment->key) == NULL ||
        my_strcat(array[pos], "=") == NULL ||
        (my_strcat(array[pos], environment->value) == NULL &&
        value_size > 0)) {
        free(array[pos]);
        return NULL;
    }
    return array[pos];
}

void destroy_environment_array(char **array)
{
    if (array == NULL)
        return;
    for (int i = 0; array[i] != NULL; i += 1)
        free(array[i]);
    free(array);
}

char **convert_environment_to_array(environment_t *environment)
{
    char **environment_array = NULL;
    int environment_array_len = 0;

    environment_array_len = get_environment_length(environment);
    environment_array = malloc(sizeof(char *) * (environment_array_len + 1));
    if (environment_array == NULL)
        return NULL;
    for (int i = 0; environment != NULL; i += 1) {
        if (add_single_variable(environment, environment_array, i) == NULL)
            return NULL;
        environment = environment->next;
    }
    environment_array[environment_array_len] = NULL;
    return environment_array;
}
