#include "message.h"

bool message_generate(struct Message *m, const char *text);

bool message_new(struct Message **message, SDL_Renderer *renderer, bool paused,
                 double delay) {

    *message = calloc(1, sizeof(struct Message));
    if (!*message) {
        fprintf(stderr, "Error in calloc of message!\n");
        return false;
    }
    struct Message *m = *message;

    m->renderer = renderer;
    m->color = (SDL_Color){FONT_COLOR};

    m->font = TTF_OpenFont("fonts/freesansbold.ttf", FONT_SIZE);
    if (!m->font) {
        fprintf(stderr, "Error creating font: %s\n", TTF_GetError());
        return false;
    }

    m->rect.x = 10;
    m->rect.y = 10;

    if (!message_update(m, paused, delay)) {
        return false;
    }

    return true;
}

void message_free(struct Message **message) {
    if (*message) {
        TTF_CloseFont((*message)->font);
        (*message)->font = NULL;

        SDL_FreeSurface((*message)->surface);
        (*message)->surface = NULL;

        SDL_DestroyTexture((*message)->image);
        (*message)->image = NULL;

        (*message)->renderer = NULL;

        free(*message);
        *message = NULL;
    }
}

bool message_update(struct Message *m, bool paused, double delay) {
    if (paused) {
        return message_generate(m, "Paused");
    } else {
        double speed = 128.0 / delay;
        int length = snprintf(NULL, 0, "Speed: %g", speed) + 1;
        char text[length];
        snprintf(text, (size_t)length, "Speed: %g", speed);
        return message_generate(m, text);
    }

    return true;
}

bool message_generate(struct Message *m, const char *text) {
    if (m->image) {
        SDL_DestroyTexture(m->image);
    }

    m->surface = TTF_RenderText_Blended(m->font, text, m->color);
    if (!m->surface) {
        fprintf(stderr, "Error creating a surface: %s\n", SDL_GetError());
        return false;
    }

    m->image = SDL_CreateTextureFromSurface(m->renderer, m->surface);
    SDL_FreeSurface(m->surface);
    m->surface = NULL;
    if (!m->image) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return false;
    }

    if (SDL_QueryTexture(m->image, NULL, NULL, &m->rect.w, &m->rect.h)) {
        fprintf(stderr, "Error while querying texture: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void message_draw(struct Message *m) {
    SDL_RenderCopy(m->renderer, m->image, NULL, &m->rect);
}
