#pragma once

#include <SDL.h>
#include "GL_bindings.hpp"

#include "debug.hpp"

namespace Main {
    extern bool running;

    extern int sdl_init();
    extern int gl_init();
    extern void handle_event(SDL_Event);
}
