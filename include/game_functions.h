/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** game_functions
*/

#ifndef GAME_FUNCTIONS_H_
    #define GAME_FUNCTIONS_H_

    #include "game.h"

    void exit_start_all(game_t *game);

    typedef struct game_functions_s {
        void (*function)(game_t *game);
    } game_functions_t;

    static const game_functions_t MENU_FLAGS[] = {
        {},
        {},
        {},
        {function : &exit_start_all},
        {function : NULL},
    };

#endif /* !GAME_FUNCTIONS_H_ */
