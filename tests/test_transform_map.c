/*
** EPITECH PROJECT, 2024
** navy01
** File description:
** test_transform_map.c
*/

#include <criterion/criterion.h>
#include "../include/player.h"
#include "../include/my_navy.h"
#include <stdlib.h>

Test(transform_map, valid_map01) {
    char *file[] = {"./my_navy", "pos1"};
    player_t *player = malloc(sizeof(player_t));
    char **map = NULL;

    player->id = 1;
    map = retrieve_info(player, file);
    transform_map(map, player);
    char *test[] = {"........",
                    "....4444",
                    "22......",
                    "...3..5.",
                    "...3..5.",
                    "...3..5.",
                    "......5.",
                    "......5."};
    cr_assert_str_eq(player->map[0], test[0]);
}
