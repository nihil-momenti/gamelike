#include "main.hpp"

#include "camera.hpp"
#include "controls.hpp"


namespace Main {
    bool grabbed = true;

    void toggle_grab() {
        grabbed = !grabbed;

        if (grabbed) {
            SDL_ShowCursor(SDL_DISABLE);
            SDL_WM_GrabInput(SDL_GRAB_ON);
        } else {
            SDL_ShowCursor(SDL_ENABLE);
            SDL_WM_GrabInput(SDL_GRAB_OFF);
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
                        if (event.key.keysym.mod & KMOD_META) {
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
                    Camera::turn(event.motion.xrel, event.motion.yrel);
                }
                return;

            case SDL_VIDEORESIZE:
                width = event.resize.w;
                height = event.resize.h;

                if (SDL_SetVideoMode(width, height, 0, SDL_OPENGL | SDL_RESIZABLE) == NULL) {
                    Debug::error << "Set Video Mode Error: " << SDL_GetError() << std::endl;
                    running = false;
                }
                gl_init();
                return;

            default:
                break;
        }

        Controls::handle_event(event);
    }
}
