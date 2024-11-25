#ifndef GAME_H
#define GAME_H

#include "main.h"

struct Game {
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
        bool is_running;
};

bool game_new(struct Game **game);
void game_free(struct Game **game);
bool game_run(struct Game *g);

#endif
