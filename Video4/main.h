#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define SDL_FLAGS (SDL_INIT_VIDEO | SDL_INIT_AUDIO)
#define IMG_FLAGS IMG_INIT_PNG

#define WINDOW_TITLE "Conway's Game of Life"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define SIZE 10
#define RENDERER_COLOR 0, 0, 0, 255
#define CELL_COLOR 128, 128, 128, 255

#endif
