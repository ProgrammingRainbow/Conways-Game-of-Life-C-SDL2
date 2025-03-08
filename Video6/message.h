#ifndef MESSAGE_H
#define MESSAGE_H

#include "main.h"

struct Message {
        SDL_Renderer *renderer;
        TTF_Font *font;
        SDL_Surface *surface;
        SDL_Texture *image;
        SDL_Rect rect;
};

bool message_new(struct Message **message, SDL_Renderer *renderer, bool paused,
                 double duration);
void message_free(struct Message **message);
bool message_update(struct Message *m, bool paused, double duration);
void message_draw(const struct Message *m);

#endif
