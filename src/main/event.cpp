#include "main.hpp"

#include "camera.hpp"

namespace Main {
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
                default:
                    break;
            }
    }
}
