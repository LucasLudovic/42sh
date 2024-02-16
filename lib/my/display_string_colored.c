/*
** EPITECH PROJECT, 2023
** MY_PUTSTR
** File description:
** Display a string
*/

#include <stdlib.h>
#include <unistd.h>
#include "color_table.h"
#include "my.h"

static
void destroy_table(color_table_t *color_table)
{
    if (color_table == NULL || color_table->name == NULL ||
        color_table->code == NULL)
        return;
    for (int i = 0; i < NB_COLOR; i += 1) {
        if (color_table->name[i] != NULL)
            free(color_table->name[i]);
        if (color_table->code[i] != NULL)
            free(color_table->code[i]);
    }
    if (color_table->name != NULL)
        free(color_table->name);
    if (color_table->code != NULL)
        free(color_table->code);
}

static
void initialize_table(color_table_t *color_table)
{
    if (color_table == NULL)
        return;
    color_table->name = malloc(sizeof(char *) * NB_COLOR);
    if (color_table->name == NULL)
        return;
    color_table->code = malloc(sizeof(char *) * NB_COLOR);
    if (color_table->name == NULL)
        return;
    color_table->name[0] = my_strdup("red");
    color_table->code[0] = my_strdup("31");
    color_table->name[1] = my_strdup("green");
    color_table->code[1] = my_strdup("32");
    color_table->name[2] = my_strdup("yellow");
    color_table->code[2] = my_strdup("33");
    color_table->name[3] = my_strdup("blue");
    color_table->code[3] = my_strdup("34");
    color_table->name[4] = my_strdup("purple");
    color_table->code[4] = my_strdup("35");
    color_table->name[5] = my_strdup("cyan");
    color_table->code[5] = my_strdup("36");
}

static
char *parse_color(color_table_t *color_table, char *color)
{
    if (color_table == NULL || color_table->name == NULL ||
        color_table->code == NULL)
        return NULL;
    for (int i = 0; i < NB_COLOR; i += 1) {
        if (my_strcmp(color_table->name[i], color) == 0)
            return color_table->code[i];
    }
    return NULL;
}

static
char *get_color_prompt(char *ansi_code)
{
    char *color_prompt = malloc(sizeof(char) * 6);

    if (color_prompt == NULL)
        return NULL;
    if (ansi_code == NULL || my_strlen(ansi_code) < 1) {
        free(color_prompt);
        return NULL;
    }
    color_prompt[0] = '\033';
    color_prompt[1] = '[';
    color_prompt[2] = '\0';
    my_strcat(color_prompt, ansi_code);
    my_strcat(color_prompt, "m");
    my_putstr(color_prompt);
    return color_prompt;
}

static
void change_text_color(char *ansi_code)
{
    char *color_prompt = NULL;

    color_prompt = get_color_prompt(ansi_code);
    if (color_prompt == NULL)
        return;
    my_putstr(color_prompt);
    if (color_prompt != NULL)
        free(color_prompt);
}

int display_string_colored(char const *str, char *color)
{
    color_table_t color_table = { 0 };
    char *ansi_code = NULL;

    if (str == NULL || color == NULL)
        return FAILURE;
    initialize_table(&color_table);
    ansi_code = parse_color(&color_table, color);
    if (ansi_code < 0)
        return FAILURE;
    change_text_color(ansi_code);
    my_putstr(str);
    change_text_color("0");
    destroy_table(&color_table);
    return SUCCESS;
}
