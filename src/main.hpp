#pragma once

#include <SDL.h>
#include "GL_bindings.hpp"

#include "debug.hpp"

#include "window.hpp"

namespace Main {
    extern bool running;
    extern int width, height;

    extern bool sdl_initialized;

    extern int sdl_init();
    extern int gl_init();
    extern void handle_event(SDL_Event);

    extern Window *window;
    extern SDL_GLContext context;
}
