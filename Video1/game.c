#include "game.h"
#include "init_sdl.h"

bool game_new(struct Game **game) {
    *game = calloc(1, sizeof(struct Game));
    if (*game == NULL) {
        fprintf(stderr, "Error in calloc of new game.\n");
        return false;
    }
    struct Game *g = *game;

    if (!game_init_sdl(g)) {
        return false;
    }

    return true;
}

void game_free(struct Game **game) {
    if (*game) {
        SDL_DestroyRenderer((*game)->renderer);
        (*game)->renderer = NULL;

        SDL_DestroyWindow((*game)->window);
        (*game)->window = NULL;

        SDL_Quit();

        free(*game);
        *game = NULL;

        printf("all clean!\n");
    }
}

bool game_run(struct Game *g) {
    SDL_RenderClear(g->renderer);

    SDL_RenderPresent(g->renderer);

    SDL_Delay(5000);

    return true;
}
