#include "game.h"
#include "init_sdl.h"

bool game_events(struct Game *g);
void game_draw(const struct Game *g);

bool game_new(struct Game **game) {
    *game = calloc(1, sizeof(struct Game));
    if (*game == NULL) {
        fprintf(stderr, "Error in calloc of new game.\n");
        return false;
    }
    struct Game *g = *game;

    g->is_running = true;

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

        IMG_Quit();
        SDL_Quit();

        free(*game);
        *game = NULL;

        printf("all clean!\n");
    }
}

bool game_events(struct Game *g) {
    while (SDL_PollEvent(&g->event)) {
        switch (g->event.type) {
        case SDL_QUIT:
            g->is_running = false;
            break;
        case SDL_KEYDOWN:
            switch (g->event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                g->is_running = false;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    return true;
}

void game_draw(const struct Game *g) {
    SDL_RenderClear(g->renderer);

    SDL_RenderPresent(g->renderer);
}

bool game_run(struct Game *g) {
    while (g->is_running) {

        if (!game_events(g)) {
            return false;
        }

        game_draw(g);

        SDL_Delay(16);
    }

    return true;
}
