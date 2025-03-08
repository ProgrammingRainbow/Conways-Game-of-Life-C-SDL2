#include "message.h"

bool message_generate(struct Message *m, const char *text);

bool message_new(struct Message **message, SDL_Renderer *renderer, bool paused,
                 double duration) {
    *message = calloc(1, sizeof(struct Message));
    if (*message == NULL) {
        fprintf(stderr, "Error in Calloc of New Message!\n");
        return false;
    }

    struct Message *m = *message;

    m->renderer = renderer;

    m->font = TTF_OpenFont("fonts/freesansbold.ttf", FONT_SIZE);
    if (!m->font) {
        fprintf(stderr, "Error creating Font: %s\n", TTF_GetError());
        return false;
    }

    m->rect.x = 10;
    m->rect.y = 10;

    if (!message_update(m, paused, duration)) {
        return false;
    }

    return true;
}

void message_free(struct Message **message) {
    if (*message) {
        struct Message *m = *message;

        if (m->image) {
            SDL_DestroyTexture(m->image);
            m->image = NULL;
        }
        if (m->surface) {
            SDL_FreeSurface(m->surface);
            m->surface = NULL;
        }
        if (m->font) {
            TTF_CloseFont(m->font);
            m->font = NULL;
        }

        m->renderer = NULL;

        free(m);
        m = NULL;
        *message = NULL;

        printf("message clean.\n");
    }
}

bool message_generate(struct Message *m, const char *text) {
    if (m->surface) {
        SDL_FreeSurface(m->surface);
        m->surface = NULL;
    }
    if (m->image) {
        SDL_DestroyTexture(m->image);
        m->image = NULL;
    }

    m->surface = TTF_RenderText_Blended(m->font, text, FONT_COLOR);
    if (!m->surface) {
        fprintf(stderr, "Error creating Surface from text: %s\n",
                TTF_GetError());
        return false;
    }

    m->rect.w = m->surface->w;
    m->rect.h = m->surface->h;

    m->image = SDL_CreateTextureFromSurface(m->renderer, m->surface);
    if (!m->image) {
        fprintf(stderr, "Error creating Texture from Surface: %s\n",
                SDL_GetError());
        return false;
    }

    return true;
}

bool message_update(struct Message *m, bool paused, double duration) {
    if (paused) {
        return message_generate(m, "Paused");
    } else {
        double speed = 128 / duration;
        int length = snprintf(NULL, 0, "Speed %g", speed) + 1;
        char text[length];
        snprintf(text, (size_t)length, "Speed %g", speed);
        return message_generate(m, text);
    }

    return true;
}

void message_draw(const struct Message *m) {
    SDL_RenderCopy(m->renderer, m->image, NULL, &m->rect);
}
