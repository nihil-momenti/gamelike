#include "main.hpp"

#include "world.hpp"
#include "world_view.hpp"
#include "camera.hpp"
#include "lights.hpp"

#include <cmath>

#include <SDL_thread.h>

const int TICKS_PER_SECOND = 25;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 2;

SDL_sem *update_semaphore;

namespace Main {
    World *world;
    WorldView *wv;
    WorldView *wv2;
    bool running = true;
    bool sdl_initialized = false;

    void Init() {
        if (sdl_init() != 0) {
            Debug::error << "Error starting SDL." << std::endl;
            running = false;
            return;
        }

        if (gl_init() != 0) {
            Debug::error << "Error loading OpenGL." << std::endl;
            running = false;
            return;
        }

        world = new World();
        wv = new WorldView(world);
        wv2 = new WorldView(world);

        window->set_world(wv);

        window2->set_world(wv);
    }

    void Event() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            handle_event(event);
        }
    }

    void Tick() {
    }

    void Render(double interpolation) {
        window->render(interpolation);
        window2->render(interpolation);
    }

    void Cleanup() {
        if (wv) {
            delete wv;
        }

        if (world) {
            delete world;
        }

        if (window2 != NULL) {
            delete window2;
        }

        if (window != NULL) {
            delete window;
        }

        if (sdl_initialized) {
            SDL_Quit();
        }
    }

    int UpdateThread(void *unused) {
        while (Main::running) {
            if (SDL_SemWait(update_semaphore) == 0) {
                Main::Tick();
            }
        }

        return 0;
    }
}

int main(int argc, char *argv[]) {
    Main::Init();

    update_semaphore = SDL_CreateSemaphore(0);
    SDL_Thread *update_thread = SDL_CreateThread(Main::UpdateThread, "Update", NULL);

    unsigned int next_game_tick = SDL_GetTicks();
    unsigned int loops = 0;

    while (Main::running) {
        loops = 0;
        while (SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP) {
            Main::Event();
            Main::window->view.camera.tick();
            Main::window2->view.camera.tick();
            next_game_tick += SKIP_TICKS;
            SDL_SemPost(update_semaphore);
            loops++;
        }
        float interpolation = (SDL_GetTicks() + SKIP_TICKS - next_game_tick) / (float) SKIP_TICKS;
        Main::Render(interpolation);
    }

    SDL_SemPost(update_semaphore);
    SDL_WaitThread(update_thread, NULL);

    Main::Cleanup();

    return 0;
}
