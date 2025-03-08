#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define SDL_FLAGS SDL_INIT_EVERYTHING
#define IMG_FLAGS IMG_INIT_PNG
#define RENDERER_FLAGS SDL_RENDERER_ACCELERATED

#define WINDOW_TITLE "Conway's Game of Life"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define CELL_SIZE 10
#define CELL_PADDING 1

#define RENDERER_COLOR 0, 0, 0, 255
#define CELL_COLOR 128, 128, 128, 255

#define TARGET_DURATION 128

#define FONT_SIZE 32
#define FONT_COLOR (SDL_Color){255, 255, 255, 255}

#endif
