#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

#define SDL_FLAGS (SDL_INIT_VIDEO | SDL_INIT_AUDIO)
#define IMG_FLAGS IMG_INIT_PNG

#define WINDOW_TITLE "Conway's Game of Life"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#endif
