#include "game.h"
#include "init_sdl.h"

bool game_toggle_pause(struct Game *g);
bool game_increase_speed(struct Game *g);
bool game_decrease_speed(struct Game *g);
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
    g->is_paused = false;

    if (!game_init_sdl(g)) {
        return false;
    }

    srand((Uint32)time(NULL));

    if (!board_new(&g->board, g->renderer)) {
        return false;
    }

    if (!fps_new(&g->fps)) {
        return false;
    }

    if (!message_new(&g->message, g->renderer, g->is_paused,
                     g->fps->target_delay)) {
        return false;
    }

    return true;
}

void game_free(struct Game **game) {
    if (*game) {
        message_free(&(*game)->message);
        fps_free(&(*game)->fps);
        board_free(&(*game)->board);

        SDL_DestroyRenderer((*game)->renderer);
        (*game)->renderer = NULL;

        SDL_DestroyWindow((*game)->window);
        (*game)->window = NULL;

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();

        free(*game);
        *game = NULL;

        printf("all clean!\n");
    }
}

bool game_toggle_pause(struct Game *g) {
    g->is_paused = !g->is_paused;
    return message_update(g->message, g->is_paused, g->fps->target_delay);
}

bool game_increase_speed(struct Game *g) {
    if (g->fps->target_delay > 8) {
        g->fps->target_delay /= 2;
        return message_update(g->message, g->is_paused, g->fps->target_delay);
    }
    return true;
}

bool game_decrease_speed(struct Game *g) {
    if (g->fps->target_delay < 1024) {
        g->fps->target_delay *= 2;
        return message_update(g->message, g->is_paused, g->fps->target_delay);
    }
    return true;
}

bool game_events(struct Game *g) {
    while (SDL_PollEvent(&g->event)) {
        switch (g->event.type) {
        case SDL_QUIT:
            g->is_running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (g->event.button.button == SDL_BUTTON_LEFT) {
                board_edit(g->board, g->event.button.x, g->event.button.y);
            }
            break;
        case SDL_KEYDOWN:
            switch (g->event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                g->is_running = false;
                break;
            case SDL_SCANCODE_SPACE:
                if (!game_toggle_pause(g)) {
                    return false;
                }
                break;
            case SDL_SCANCODE_UP:
                if (!game_increase_speed(g)) {
                    return false;
                }
                break;
            case SDL_SCANCODE_DOWN:
                if (!game_decrease_speed(g)) {
                    return false;
                }
                break;
            case SDL_SCANCODE_R:
                board_reset(g->board);
                break;
            case SDL_SCANCODE_C:
                board_clear(g->board);
                break;
            case SDL_SCANCODE_F:
                fps_toggle_display(g->fps);
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
    SDL_SetRenderDrawColor(g->renderer, RENDERER_COLOR);
    SDL_RenderClear(g->renderer);

    board_draw(g->board);
    message_draw(g->message);

    SDL_RenderPresent(g->renderer);
}

bool game_run(struct Game *g) {
    while (g->is_running) {

        if (!game_events(g)) {
            return false;
        }

        if (!g->is_paused) {
            board_update(g->board);
        }

        game_draw(g);

        fps_update(g->fps);
    }

    return true;
}
