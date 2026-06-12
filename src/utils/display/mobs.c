/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** mobs
*/

#include "game.h"
#include "display.h"
#include "mobs_functions.h"

void display_mobs(game_t *game)
{
    int i = 0;

    if (game->menu < 5 || game->menu > 6)
        return;
    manage_mobs(game);
    for (i = 0; game->mobs[i] != NULL; i++) {
        if (game->mobs[i]->is_alive == sfFalse)
            continue;
        sfRenderWindow_drawSprite(game->window->window,
            game->mobs[i]->sprite, NULL);
    }
}
