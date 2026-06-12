/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** rpg
*/

#ifndef RPG_H_
    #define RPG_H_

    #include <CSFML/Graphics.h>
    #include <CSFML/Audio.h>
    #include <CSFML/Window.h>
    #include <CSFML/Network.h>

    #include <stdlib.h>
    #include <stdbool.h>

    #ifndef SFBOOL_DEFINED
        typedef enum {
            sfFalse = 0,
            sfTrue = 1
        } sfBool;
        #define SFBOOL_DEFINED
    #endif

    #define EPITECH_ERROR 84
    #define EPITECH_SUCCESS 0

#endif /* !RPG_H_ */
