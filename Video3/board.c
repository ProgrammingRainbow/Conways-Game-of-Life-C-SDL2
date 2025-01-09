#include "board.h"

bool board_new(struct Board **board, SDL_Renderer *renderer) {
    *board = calloc(1, sizeof(struct Board));
    if (*board == NULL) {
        fprintf(stderr, "Error in calloc of new Board.\n");
        return false;
    }
    struct Board *b = *board;

    b->renderer = renderer;
    b->rows = WINDOW_HEIGHT / SIZE;
    b->columns = WINDOW_WIDTH / SIZE;

    b->board = calloc(1, sizeof(bool) * (Uint64)(b->rows * b->columns));
    if (b->board == NULL) {
        fprintf(stderr, "Error in calloc of new board.\n");
        return false;
    }

    b->next_board = calloc(1, sizeof(bool) * (Uint64)(b->rows * b->columns));
    if (b->next_board == NULL) {
        fprintf(stderr, "Error in calloc of new board.\n");
        return false;
    }

    board_reset(b);

    return true;
}

void board_free(struct Board **board) {
    if (*board) {
        free((*board)->board);
        (*board)->board = NULL;

        free((*board)->next_board);
        (*board)->next_board = NULL;

        (*board)->renderer = NULL;

        free(*board);
        *board = NULL;
    }
}

void board_reset(struct Board *b) {
    for (int row = 0; row < b->rows * b->columns; row += b->columns) {
        for (int column = 0; column < b->columns; column++) {
            if (rand() % 2 == 0) {
                b->board[row + column] = true;
            } else {
                b->board[row + column] = false;
            }
        }
    }
}

void board_clear(struct Board *b) {
    for (int row = 0; row < b->rows * b->columns; row += b->columns) {
        for (int column = 0; column < b->columns; column++) {
            b->board[row + column] = false;
        }
    }
}

void board_draw(const struct Board *b) {
    SDL_SetRenderDrawColor(b->renderer, CELL_COLOR);
    SDL_Rect rect = {0, 0, SIZE - 1, SIZE - 1};
    for (int row = 0; row < b->rows; row++) {
        rect.y = SIZE * row;
        for (int column = 0; column < b->columns; column++) {
            rect.x = SIZE * column;
            if (b->board[row * b->columns + column]) {
                SDL_RenderFillRect(b->renderer, &rect);
            }
        }
    }
}
