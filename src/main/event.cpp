#include "main.hpp"

#include "camera.hpp"
#include "controls.hpp"


namespace Main {
    bool grabbed = true;

    void toggle_grab() {
        grabbed = !grabbed;

        if (grabbed) {
            SDL_SetRelativeMouseMode(SDL_TRUE);
        } else {
            SDL_SetRelativeMouseMode(SDL_FALSE);
        }
    }

    void handle_event(SDL_Event event) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                return;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_q:
                        if (event.key.keysym.mod & KMOD_GUI) {
                            running = false;
                            return;
                        }
                        break;
                    case SDLK_ESCAPE:
                        toggle_grab();
                        return;
                    default:
                        break;
                }
                break;

            case SDL_MOUSEMOTION:
                if (grabbed) {
                    window->view.camera.turn(event.motion.xrel, event.motion.yrel);
                    window2->view.camera.turn(event.motion.xrel, event.motion.yrel);
                }
                return;

           case SDL_WINDOWEVENT:
                if (window->window_id == event.window.windowID) {
                    window->handle_event(event.window);
                }
                if (window2->window_id == event.window.windowID) {
                    window2->handle_event(event.window);
                }
                return;

            default:
                break;
        }

        Controls::handle_event(event);
    }
}
