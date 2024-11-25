#ifndef BOARD_H
#define BOARD_H

#include "main.h"

struct Board {
        SDL_Renderer *renderer;
        bool *board;
        bool *next_board;
        int rows;
        int columns;
        SDL_Rect rect;
};

bool board_new(struct Board **board, SDL_Renderer *renderer);
void board_free(struct Board **board);
void board_reset(struct Board *b);
void board_clear(struct Board *b);
void board_draw(struct Board *b);

#endif
