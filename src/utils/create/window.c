/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** window
*/

#include "game.h"
#include <stdio.h>

void create_window(game_t *game)
{
    game->window = malloc(sizeof(window_t));
    game->window->title = "Start";

    fprintf(stderr, "DEBUG: Creating window with mode size: %u x %u\n", 
        game->params->mode.size.x, game->params->mode.size.y);
    game->window->window = sfRenderWindow_create(game->params->mode,
        game->window->title, sfClose | sfResize, sfWindowed, NULL);
    
    if (!game->window->window) {
        fprintf(stderr, "ERROR: Failed to create window\n");
        return;
    }
    fprintf(stderr, "DEBUG: Window created successfully\n");

    game->window->view = sfView_createFromRect(
        (sfFloatRect){.position = {0, 0}, .size = {1920, 1080}});
    sfRenderWindow_setFramerateLimit(game->window->window, 3000);
    sfRenderWindow_setVerticalSyncEnabled(game->window->window, sfTrue);
    sfRenderWindow_setView(game->window->window, game->window->view);

    game->window->song = malloc(sizeof(song_t));
    game->window->song->music =
        sfMusic_createFromFile("assets/songs/main.ogg");
    if (!game->window->song->music) {
        fprintf(stderr, "ERROR: Failed to load music\n");
    } else {
        fprintf(stderr, "DEBUG: Music loaded successfully\n");
    }
    sfMusic_setLooping(game->window->song->music, sfTrue);
    sfMusic_setVolume(game->window->song->music, game->params->volume);
    sfMusic_play(game->window->song->music);
}
