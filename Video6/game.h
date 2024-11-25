#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "fps.h"
#include "main.h"
#include "message.h"

struct Game {
        SDL_Window *window;
        SDL_Renderer *renderer;
        struct Board *board;
        struct Fps *fps;
        struct Message *message;
        SDL_Event event;
        bool is_running;
        bool is_paused;
};

bool game_new(struct Game **game);
void game_free(struct Game **game);
bool game_run(struct Game *g);

#endif
