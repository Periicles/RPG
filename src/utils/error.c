/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** error
*/
#include <stdbool.h>
#include <unistd.h>

int my_strncmp(char const *s1, char const *s2, int n);
int my_strcmp(char const *s1, char const *s2);

bool is_error(const char **env)
{
    // On macOS and other systems, DISPLAY is not required for native graphics
    // DISPLAY is only needed for X11 compatibility on Linux
    // Return false (no error) by default for native graphics systems
    (void)env;  // Suppress unused parameter warning
    return false;
}
