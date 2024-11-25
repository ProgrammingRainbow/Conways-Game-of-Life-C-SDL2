#include "init_sdl.h"

bool game_init_sdl(struct Game *g) {

    if (SDL_Init(SDL_FLAGS)) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }

    int img_init = IMG_Init(IMG_FLAGS);
    if ((img_init & IMG_FLAGS) != IMG_FLAGS) {
        fprintf(stderr, "Error initializing SDL_image: %s\n", IMG_GetError());
        return false;
    }

    g->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                 WINDOW_HEIGHT, 0);
    if (!g->window) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        return false;
    }

    g->renderer = SDL_CreateRenderer(g->window, -1, SDL_RENDERER_ACCELERATED);
    if (!g->renderer) {
        fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
        return false;
    }

    SDL_Surface *icon_surf = IMG_Load("images/icon.png");
    if (icon_surf) {
        SDL_SetWindowIcon(g->window, icon_surf);
        SDL_FreeSurface(icon_surf);
    } else {
        fprintf(stderr, "Error creating icon surface: %s\n", SDL_GetError());
        return false;
    }

    return true;
}
