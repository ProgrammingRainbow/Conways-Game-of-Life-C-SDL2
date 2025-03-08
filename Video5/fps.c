#include "fps.h"

Uint32 fps_time_since(Uint32 last_time, Uint32 *new_last_time);
void fps_update_display(struct Fps *f);

bool fps_new(struct Fps **fps) {
    *fps = calloc(1, sizeof(struct Fps));
    if (*fps == NULL) {
        fprintf(stderr, "Error in Calloc of New Fps!\n");
        return false;
    }

    struct Fps *f = *fps;

    f->last_time = SDL_GetTicks();
    f->target_duration = TARGET_DURATION;
    f->carry_delay = 0;
    f->max_delay = 50;
    f->fps_last_time = f->last_time;
    f->fps_counter = 0;
    f->fps_display = false;

    return true;
}

void fps_free(struct Fps **fps) {
    if (*fps) {
        free(*fps);
        *fps = NULL;
    }

    printf("clean fps.\n");
}

void fps_display_toggle(struct Fps *f) {
    if (f->fps_display) {
        f->fps_display = false;
    } else {
        f->fps_display = true;
        f->fps_counter = 0;
        f->fps_last_time = SDL_GetTicks();
    }
}

void fps_increase_speed(struct Fps *f) {
    if (f->target_duration > 8) {
        f->target_duration /= 2;
    }
}

void fps_decrease_speed(struct Fps *f) {
    if (f->target_duration < 1024) {
        f->target_duration *= 2;
    }
}

Uint32 fps_time_since(Uint32 last_time, Uint32 *new_last_time) {
    Uint32 current_time = SDL_GetTicks();
    Uint32 elapsed_time = 0;

    if (current_time < last_time) {
        elapsed_time = (Uint32)-1 - last_time + current_time;
    } else {
        elapsed_time = current_time - last_time;
    }

    if (new_last_time) {
        *new_last_time = current_time;
    }

    return elapsed_time;
}

void fps_update_display(struct Fps *f) {
    if (f->fps_display) {
        if (fps_time_since(f->fps_last_time, NULL) >= 1000) {
            printf("%i\n", f->fps_counter);
            f->fps_counter = 0;
            f->fps_last_time += 1000;
        }
        f->fps_counter++;
    }
}

void fps_update(struct Fps *f) {
    Uint32 elapsed_time = fps_time_since(f->last_time, NULL);
    double duration = f->target_duration + f->carry_delay;

    if (duration > elapsed_time) {
        Uint32 delay = (Uint32)duration - elapsed_time;
        SDL_Delay(delay);
    }

    elapsed_time = fps_time_since(f->last_time, &f->last_time);

    f->carry_delay = duration - elapsed_time;
    if (f->carry_delay > f->max_delay) {
        f->carry_delay = f->max_delay;
    } else if (f->carry_delay < -f->max_delay) {
        f->carry_delay = -f->max_delay;
    }

    fps_update_display(f);
}
