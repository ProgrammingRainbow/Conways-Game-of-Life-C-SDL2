#ifndef MESSAGE_H
#define MESSAGE_H

#include "main.h"

struct Message {
        SDL_Renderer *renderer;
        SDL_Surface *surface;
        SDL_Texture *image;
        TTF_Font *font;
        SDL_Color color;
        SDL_Rect rect;
};

bool message_new(struct Message **message, SDL_Renderer *renderer, bool playing,
                 double speed);
void message_free(struct Message **message);
bool message_update(struct Message *m, bool playing, double delay);
void message_draw(const struct Message *m);

#endif
