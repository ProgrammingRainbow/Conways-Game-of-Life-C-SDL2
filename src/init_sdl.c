#include "init_sdl.h"

bool game_init_sdl(struct Game *g) {
    if (SDL_Init(SDL_FLAGS)) {
        fprintf(stderr, "Error initializing SDL2. %s\n", SDL_GetError());
        return false;
    }

    if ((IMG_Init(IMG_FLAGS) & IMG_FLAGS) != IMG_FLAGS) {
        fprintf(stderr, "Error initializing SDL_image. %s\n", IMG_GetError());
        return false;
    }

    if (TTF_Init()) {
        fprintf(stderr, "Error initializing SDL_ttf. %s\n", TTF_GetError());
        return false;
    }

    g->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                 WINDOW_HEIGHT, 0);
    if (!g->window) {
        fprintf(stderr, "Error creating SDL_Window. %s\n", SDL_GetError());
        return false;
    }

    g->renderer = SDL_CreateRenderer(g->window, -1, RENDERER_FLAGS);
    if (!g->renderer) {
        fprintf(stderr, "Error creating SDL_Renderer. %s\n", SDL_GetError());
        return false;
    }

    SDL_Surface *icon_surf = IMG_Load("images/icon.png");
    if (!icon_surf) {
        fprintf(stderr, "Error loading SDL_Surface. %s\n", IMG_GetError());
        return false;
    }
    SDL_SetWindowIcon(g->window, icon_surf);
    SDL_FreeSurface(icon_surf);
    icon_surf = NULL;

    return true;
}
