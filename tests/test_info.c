/*
** EPITECH PROJECT, 2024
** navy01
** File description:
** test_retieveinfo.c
*/

#include <criterion/criterion.h>
#include "../include/player.h"
#include "../include/my_navy.h"
#include <stdlib.h>
#include <stdio.h>


Test(retrieve_info, valid_map01) {
    char *file[] = {"./my_navy", "pos1"};
    player_t *player = malloc(sizeof(player_t));
    char **map = NULL;

    player->id = 1;
    map = retrieve_info(player, file);
    char *test[] = {"2:C1:C2",
                    "3:D4:F4",
                    "4:B5:B8",
                    "5:D7:H7"};
    cr_assert_str_eq(map[0], test[0]);
}

Test(retrieve_info, valid_map02) {
    char *file[] = {"./my_navy", "pos1"};
    player_t *player = malloc(sizeof(player_t));
    char **map = NULL;

    player->id = 1;
    map = retrieve_info(player, file);
    char *test[] = {"2:C1:C2",
                    "3:D4:F4",
                    "4:B5:B8",
                    "5:D7:H7"};
    cr_assert_str_eq(map[1], test[1]);
}

Test(retrieve_info, valid_map03) {
    char *file[] = {"./my_navy", "pos1"};
    player_t *player = malloc(sizeof(player_t));
    char **map = NULL;

    player->id = 1;
    map = retrieve_info(player, file);
    char *test[] = {"2:C1:C2",
                    "3:D4:F4",
                    "4:B5:B8",
                    "5:D7:H7"};
    cr_assert_str_eq(map[3], test[3]);
}

Test(retrieve_info, valid_map04) {
    char *file[] = {"./my_navy", "pos1"};
    player_t *player = malloc(sizeof(player_t));
    char **map = NULL;

    player->id = 1;
    map = retrieve_info(player, file);
    cr_assert_null(map[4]);
}
