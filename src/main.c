/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** main
*/

#include "game.h"
#include <CSFML/Window/Keyboard.h>
#include <stdio.h>

void do_free(game_t *game);
bool is_error(const char **env);
int start_game(game_t *game);
network_t *connect_to_server(void);

int main(int ac, char **av, const char **env)
{
    (void)ac;
    (void)av;
    fprintf(stderr, "DEBUG: Starting game\n");
    if (is_error(env)) {
        fprintf(stderr, "ERROR: is_error check failed (no DISPLAY)\n");
        return 84;
    }
    fprintf(stderr, "DEBUG: is_error passed\n");
    game_t game = {0};
    fprintf(stderr, "DEBUG: Connecting to server\n");
    game.network = connect_to_server();
    fprintf(stderr, "DEBUG: Network status: %s\n", game.network == NULL ? "NULL" : "OK");
    fprintf(stderr, "DEBUG: Starting game loop\n");
    start_game(&game);
    fprintf(stderr, "DEBUG: Game ended\n");
    do_free(&game);
    return (0);
}
