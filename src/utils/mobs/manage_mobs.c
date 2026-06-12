/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** mobs
*/

#include <math.h>

#include "game.h"
#include "mobs_functions.h"

static sfVector2f update_and_draw_ennemy(game_t *game, int i)
{
    mobs_t *mob = game->mobs[i];
    sfVector2f mob_pos = mob->pos;
    float dx = 0;
    float dy = 0;

    mob_pos.x -= game->map->rect.position.x * 3;
    mob_pos.y -= game->map->rect.position.y * 3;
    dx = game->perso->pos.x + mob->TextureRect.size.x / 2.0 - mob_pos.x;
    dy = game->perso->pos.y + mob->TextureRect.size.y / 2.0 - mob_pos.y;
    mob->distance_to_player = sqrt(pow(dx, 2) + pow(dy, 2));
    sfSprite_setPosition(mob->sprite, mob_pos);
    sfSprite_setTextureRect(mob->sprite, mob->TextureRect);
    return mob_pos;
}

static void change_ennemi_status(game_t *game, int i)
{
    mobs_t *mob = game->mobs[i];

    if (mob->state != Attacking && mob->distance_to_player < 300)
        mob->state = Attacking;
    if (mob->state == Attacking && mob->distance_to_player > 500)
        mob->state = Neutral;
}

static void reward_kill(game_t *game, mobs_t *mob)
{
    mob->is_alive = sfFalse;
    game->perso->combat->defense += 1;
    game->perso->combat->life += 10;
    game->perso->combat->attack += 3;
    game->perso->combat->strength += 1;
    game->nb_mob_killed += 1;
    if (mob->mob_type != 1)
        return;
    game->game_menu->quest->nb_achievement += 1;
    game->is_finished = true;
    game->menu = 42;
}

static void win_perso(game_t *game, mobs_t *mob)
{
    if (sfKeyboard_isKeyPressed(game->keys->attack)
        && mob->distance_to_player < 50) {
        if (mob->combat->life > 0) {
            mob->combat->life -= 10;
            return;
        }
        reward_kill(game, mob);
    }
    if (game->perso->combat->life > 100)
        game->perso->combat->life = 100;
    if (game->perso->combat->life <= 0) {
        game->perso->combat->life = 0;
        game->is_finished = true;
        game->menu = -42;
    }
}

static void level_up_mobs(game_t *game)
{
    int i = 0;

    if (game->nb_mob_killed % 3 == 0 && game->params->tmp == 0) {
        for (i = 0; game->mobs[i] != NULL; i++) {
            game->mobs[i]->combat->life += 1;
            game->mobs[i]->combat->attack += 2;
        }
        game->params->tmp = 1;
    }
    if (game->nb_mob_killed % 3 != 0)
        game->params->tmp = 0;
}

static void anime_ennemie(game_t *game, mobs_t *mob)
{
    if (sfClock_getElapsedTime(mob->clock_anime).microseconds / 1000000.0
        > 0.7) {
        mob->TextureRect.position.x += mob->left_display;
        if (mob->TextureRect.position.x >= 70)
            mob->TextureRect.position.x = 0;
        sfClock_restart(mob->clock_anime);
    }
    level_up_mobs(game);
}

static void attack_player(game_t *game, int i, const sfVector2f *mob_pos)
{
    mobs_t *mob = game->mobs[i];
    sfVector2f offset = {game->perso->pos.x + 22 - mob_pos->x,
        game->perso->pos.y + 25 - mob_pos->y};

    if (mob->state == Attacking && mob->distance_to_player > 50)
        move_ennemi(game, i, &offset, mob_pos);
    if (mob->state == Attacking && mob->distance_to_player < 70
        && sfClock_getElapsedTime(mob->clock).microseconds / 1000000.0 > 1.0) {
        game->perso->combat->life -= game->perso->combat->defense;
        sfClock_restart(mob->clock);
    }
}

void manage_mobs(game_t *game)
{
    sfVector2f mob_pos = {0, 0};
    int i = 0;

    for (i = 0; game->mobs[i] != NULL; i++) {
        if (game->mobs[i]->is_alive == sfFalse)
            continue;
        mob_pos = update_and_draw_ennemy(game, i);
        change_ennemi_status(game, i);
        attack_player(game, i, &mob_pos);
        anime_ennemie(game, game->mobs[i]);
        win_perso(game, game->mobs[i]);
    }
}
