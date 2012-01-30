#include "controls.hpp"

#include "main.hpp"

namespace Controls {
    bool handle_movement(SDL_Keysym key, int state) {
        Direction direction;

        switch (key.sym) {
            case SDLK_w:      direction = FORWARD; break;
            case SDLK_a:      direction = LEFT;    break;
            case SDLK_s:      direction = BACK;    break;
            case SDLK_d:      direction = RIGHT;   break;
            case SDLK_SPACE:  direction = UP;      break;
            case SDLK_LSHIFT: direction = DOWN;    break;
            default:                               return false;
        }

        state == SDL_PRESSED ? Main::window->view.camera.move(direction) : Main::window->view.camera.stop(direction);
        return true;
    }

    bool handle_event(SDL_Event event) {
        switch (event.type) {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                if (handle_movement(event.key.keysym, event.key.state)) {
                    return true;
                }
                break;
        }

        return false;
    }
}
