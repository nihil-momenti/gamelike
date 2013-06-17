#pragma once

#include <SDL.h>
#include <algorithm>
#include <string>

#include "view.hpp"
#include "world_view.hpp"

struct WindowSettings {
    std::string name;
    struct Size {
        int width;
        int height;
    } size;
    struct Position {
        int x;
        int y;
    } topleft;
};

class Window {
    public:
        Window(WindowSettings);
        ~Window();

        void gl_init();

        void set_world(WorldView *);
        void render(double);
        void handle_event(SDL_WindowEvent &);

        int window_id;
        bool error;
        const char *error_msg;
        SDL_GLContext context;

        View view;

    private:
        SDL_Window *sdl_window;
};
