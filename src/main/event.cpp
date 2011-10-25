#include "main.hpp"

#include "camera.hpp"


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
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_q:
                            if ((event.key.keysym.mod & KMOD_META) != 0) {
                                running = false;
                            }
                            break;
                        case SDLK_w:
                            Camera::move(FORWARD);
                            break;
                        case SDLK_a:
                            Camera::move(LEFT);
                            break;
                        case SDLK_s:
                            Camera::move(BACK);
                            break;
                        case SDLK_d:
                            Camera::move(RIGHT);
                            break;
                        case SDLK_SPACE:
                            Camera::move(UP);
                            break;
                        case SDLK_z:
                            Camera::move(DOWN);
                            break;
                        case SDLK_ESCAPE:
                            toggle_grab();
                            break;
                        default:
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                            Camera::stop(FORWARD);
                            break;
                        case SDLK_a:
                            Camera::stop(LEFT);
                            break;
                        case SDLK_s:
                            Camera::stop(BACK);
                            break;
                        case SDLK_d:
                            Camera::stop(RIGHT);
                            break;
                        case SDLK_SPACE:
                            Camera::stop(UP);
                            break;
                        case SDLK_z:
                            Camera::stop(DOWN);
                            break;
                        default:
                            break;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (grabbed) {
                        Camera::turn(event.motion.xrel, event.motion.yrel);
                    }
                    break;

                case SDL_VIDEORESIZE:
                    width = event.resize.w;
                    height = event.resize.h;

                    if (SDL_SetVideoMode(width, height, 0, SDL_OPENGL | SDL_RESIZABLE) == NULL) {
                        Debug::error << "Set Video Mode Error: " << SDL_GetError() << std::endl;
                        running = false;
                    }
                    gl_init();
                    break;

                default:
                    break;
            }
    }
}
