/*
** EPITECH PROJECT, 2024
** Which
** File description:
** Get the directory of binary in path for the minishell project
*/

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "my.h"
#include "dependencies/environment.h"
#include "my_macros.h"

static
char *get_path(environment_t *environment)
{
    while (environment != NULL) {
        if (environment->key == NULL || environment->value == NULL) {
            environment = environment->next;
            continue;
        }
        if (my_strcmp(environment->key, "PATH") == 0)
            return my_strdup(environment->value);
        environment = environment->next;
    }
    return NULL;
}

static
int check_file_in_dir(DIR *directory, const char *file_name)
{
    struct dirent *file = readdir(directory);

    while (file != NULL) {
        if (my_strcmp(file_name, file->d_name) == 0)
            return TRUE;
        file = readdir(directory);
    }
    return FALSE;
}

static
char *get_file_path(DIR *directory, const char *solo_path,
    const char *file_name)
{
    char *absolute_path = NULL;
    int len_absolute_path = 0;

    if (solo_path == NULL || file_name == NULL)
        return NULL;
    if (!check_file_in_dir(directory, file_name))
        return NULL;
    len_absolute_path = my_strlen(solo_path) + my_strlen(file_name);
    if (solo_path[my_strlen(solo_path) - 1] != '/')
        len_absolute_path += 1;
    absolute_path = malloc(sizeof(char) * (len_absolute_path + 1));
    my_strcpy(absolute_path, solo_path);
    if (solo_path[my_strlen(solo_path) - 1] != '/')
        my_strcat(absolute_path, "/");
    my_strcat(absolute_path, file_name);
    return absolute_path;
}

static
char *retrieve_function_path(char *path, const char *file_name)
{
    char *solo_path = NULL;
    char *absolute_file_path = NULL;
    DIR *directory = NULL;

    if (path == NULL || file_name == NULL)
        return NULL;
    solo_path = strtok(path, ":");
    while (solo_path != NULL) {
        directory = opendir(solo_path);
        if (directory == NULL) {
            display_error("Wrong directory in PATH\n");
            return NULL;
        }
        absolute_file_path = get_file_path(directory, solo_path, file_name);
        closedir(directory);
        if (absolute_file_path != NULL)
            return absolute_file_path;
        solo_path = strtok(NULL, ":");
    }
    return NULL;
}

char *get_function_absolute_path(environment_t *environment,
    char **arguments)
{
    char *path = NULL;
    char *function_absolute_path = NULL;

    if (environment == NULL)
        return NULL;
    path = get_path(environment);
    if (path == NULL)
        return NULL;
    function_absolute_path = retrieve_function_path(path, arguments[0]);
    if (path != NULL)
        free(path);
    return function_absolute_path;
}
